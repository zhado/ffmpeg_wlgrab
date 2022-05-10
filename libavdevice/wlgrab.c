/*
 * sandro wayland grabber
 * Copyright (C) 2014 sandro razmadze
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "config.h"
#include "../../../../zad_stopwatch.h"

#include <libavutil/avutil.h>
#include <libavutil/log.h>
#include <libavutil/rational.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <fcntl.h>

#include "libavutil/internal.h"
#include "libavutil/mathematics.h"
#include "libavutil/opt.h"
#include "libavutil/parseutils.h"
#include "libavutil/time.h"

#include "libavformat/avformat.h"
#include "libavformat/internal.h"
#include "libavformat/internal.h"

#include "wayland_protocols/wlr-screencopy-unstable-v1-client-protocol.h"

typedef struct WLGrabContext {
	const AVClass *class;

	struct wl_display* display;
	struct wl_compositor* compositor;
	struct wl_output* output;
	struct wl_shm* shm ;
	struct zwlr_screencopy_manager_v1* screencopy_manager;
	struct zxdg_output_manager_v1* zxdg_output_manager;
	struct zxdg_output_v1 *zxdg_output;

	int output_width;
	int output_height;
	int output_x;
	int output_y;
	char output_name[100];

	struct zwlr_screencopy_frame_v1 *frame;
	bool first_frame;
	enum wl_shm_format frame_format;

	uint32_t frame_width;
	uint32_t frame_height;
	uint32_t frame_stride;
	uint64_t frame_size_bytes;
	int64_t pts;

	struct wl_buffer *frame_buffer;
	
	void* frame_bytes;
	uint64_t written_bytes;

	uint64_t last_pts;

} WLGrabContext;

#define OFFSET(x) offsetof(WLGrabContext, x)
#define D AV_OPT_FLAG_DECODING_PARAM
static const AVOption options[] = {
    /*{ "output_x", "Initial x coordinate.", OFFSET(output_x), AV_OPT_TYPE_INT, { .i64 = 0 }, 0, INT_MAX, D },*/
    /*{ "framerate", "", OFFSET(framerate), AV_OPT_TYPE_STRING, {.str = "ntsc" }, 0, 0, D },*/
    { NULL },
};

static void global_registry_handler(void *data, struct wl_registry *registry, uint32_t id,const char *interface, uint32_t version)
{
	WLGrabContext* way_bs=(WLGrabContext*)data;
	if (strcmp(interface, "wl_compositor") == 0)
		way_bs->compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 1);
	if (strcmp(interface, wl_output_interface.name) == 0)
	{
		way_bs->output = (struct wl_output*)wl_registry_bind(registry, id, &wl_output_interface, 1);
	}
	else if (strcmp(interface, wl_shm_interface.name) == 0)
	{
		way_bs->shm = (struct wl_shm*) wl_registry_bind(registry, id, &wl_shm_interface, 1);
	}
	else if (strcmp(interface, zwlr_screencopy_manager_v1_interface.name) == 0)
	{
		way_bs->screencopy_manager = (struct zwlr_screencopy_manager_v1*) wl_registry_bind(registry, id,&zwlr_screencopy_manager_v1_interface, 2);
	}
}

static void global_registry_remover(void *data, struct wl_registry *registry, uint32_t id)
{
    printf("Got a registry losing event for %d\n", id);
}


// aedan frame ebis yleobebi

//https://stackoverflow.com/questions/22886312/a-bit-number-of-color-channel-of-rgb-argb-and-rgba
static void frame_handle_buffer(void* data, struct zwlr_screencopy_frame_v1 *frame, enum wl_shm_format format,uint32_t width, uint32_t height, uint32_t stride){
	WLGrabContext* way_bs=(WLGrabContext*)data;
	/*printf("got buffer\n");*/
	if(way_bs->first_frame){
		way_bs->frame_width=width;
		way_bs->frame_height=height;
		way_bs->frame_stride=stride;
		way_bs->frame_format=format;
		printf("%u\n",format);
	}else{
		/*zwlr_screencopy_frame_v1_copy_with_damage(frame, way_bs->frame_buffer);*/
		zwlr_screencopy_frame_v1_copy(frame, way_bs->frame_buffer);
		/*printf("dakopirda\n");*/
	}

	/*zwlr_screencopy_frame_v1_copy_with_damage(frame, buffer.wl_buffer);*/
}

static void frame_handle_flags(void* data, struct zwlr_screencopy_frame_v1* zwlr_screencopy_frame_v1 , uint32_t flags) {
	/*printf("got flags\n");*/
}

static void frame_handle_ready(void* data, struct zwlr_screencopy_frame_v1* zwlr_screencopy_frame_v1,uint32_t tv_sec_hi, uint32_t tv_sec_low, uint32_t tv_nsec) {
	WLGrabContext* way_bs=(WLGrabContext*)data;
	way_bs->pts= ((((uint64_t)tv_sec_hi) << 32) | tv_sec_low) * 1000000000 + tv_nsec;
	way_bs->pts/=1000;
	zwlr_screencopy_frame_v1_destroy(way_bs->frame);
	/*printf("frame ready\n");*/
	/*for(uint64_t i=0;i<way_bs->frame_size_bytes;i++){*/
		/*way_bs->written_bytes++;*/
	/*}*/
	/*write(file_out_fd,way_bs->frame_bytes,way_bs->frame_size_bytes);*/
}

static void frame_handle_failed(void* data, struct zwlr_screencopy_frame_v1 * frame) {
	/*WLGrabContext* way_bs=(WLGrabContext*)data;*/
	printf("cant get frame\n");
}

static void frame_handle_damage(void* data, struct zwlr_screencopy_frame_v1* zwlr_screencopy_frame_v1, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {

}

static const AVClass wlgrab_class = {
    .class_name = "wlgrab indev",
    .item_name  = av_default_item_name,
    .option     = options,
    .version    = LIBAVUTIL_VERSION_INT,
    .category   = AV_CLASS_CATEGORY_DEVICE_VIDEO_INPUT,
};

static const struct wl_registry_listener registry_listener = {
	global_registry_handler,
	global_registry_remover
};

static struct zwlr_screencopy_frame_v1_listener frame_listener = {
	.buffer = frame_handle_buffer,
	.flags = frame_handle_flags,
	.ready = frame_handle_ready,
	.failed = frame_handle_failed,
	.damage = frame_handle_damage,
};

static void* get_frames(void* thread_data){
	WLGrabContext* way_bs=(WLGrabContext*)thread_data;
	while(1){
		way_bs->frame = zwlr_screencopy_manager_v1_capture_output(way_bs->screencopy_manager, 1, way_bs->output);
		zwlr_screencopy_frame_v1_add_listener(way_bs->frame, &frame_listener, way_bs);
		wl_display_dispatch(way_bs->display);
		
		// to dispatch the copy
		wl_display_dispatch(way_bs->display);
		/*break;*/
	}
	return 0;
}

static int wlgrab_read_header(AVFormatContext *s){

	AVStream *st ;
	WLGrabContext* way_bs;
	struct wl_registry *registry;
	char shm_file_name[] = "/tmp/shared-mem-XXXXXX";
	int fd;
	int ret;
	struct wl_shm_pool *pool;
	pthread_t frame_thr;


	way_bs=s->priv_data;
	way_bs->display = wl_display_connect(NULL);
	st = avformat_new_stream(s, NULL);

	/*[>[>file_out_fd = open("sandro_frame", O_WRONLY | O_CREAT, 0666);<]<]*/
	/*[>[>if(file_out_fd<0){ printf("file ver shevqmeni\n"); exit(1);}<]<]*/

	if (way_bs->display == NULL)
	{
		fprintf(stderr, "failed to create display: %m\n");
		return EXIT_FAILURE;
	}
	registry = wl_display_get_registry(way_bs->display);
	wl_registry_add_listener(registry, &registry_listener, way_bs);

	wl_display_dispatch(way_bs->display);
	wl_display_roundtrip(way_bs->display);


// kadrebis migeba aqedan iwyeba
// jer pirvelad vidzaxebt rom info ebi gavigot
// amaze siroba api ar arsebobs miwaze

	way_bs->first_frame=true;
	way_bs->frame = zwlr_screencopy_manager_v1_capture_output(way_bs->screencopy_manager, 1, way_bs->output);

	zwlr_screencopy_frame_v1_add_listener(way_bs->frame, &frame_listener, way_bs);

	wl_display_dispatch(way_bs->display);
	wl_display_roundtrip(way_bs->display);

	way_bs->first_frame=false;
	way_bs->frame_size_bytes=way_bs->frame_height*way_bs->frame_stride;

	// crate shared memory
	fd = mkstemp(shm_file_name);
	if (fd < 0) { printf("cant make fd\n"); }

	while ((ret = ftruncate(fd, way_bs->frame_size_bytes)) == EINTR) { }
	if (ret < 0) { close(fd); }

	// to make it anonymoose :D
	unlink(shm_file_name);

	way_bs->frame_bytes = mmap(NULL, way_bs->frame_size_bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (way_bs->frame_bytes == MAP_FAILED) { printf("mmap fail\n"); }

	pool = wl_shm_create_pool(way_bs->shm, fd, way_bs->frame_size_bytes);
	close(fd);
	way_bs->frame_buffer = wl_shm_pool_create_buffer(pool, 0, way_bs->frame_width, way_bs->frame_height,way_bs->frame_stride, way_bs->frame_format);
	wl_shm_pool_destroy(pool);
	way_bs->written_bytes=0;
	zwlr_screencopy_frame_v1_destroy(way_bs->frame);
 
	
	st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
	st->codecpar->codec_id = AV_CODEC_ID_RAWVIDEO;
	st->codecpar->width  = way_bs->frame_width;
	st->codecpar->height = way_bs->frame_height;
	/*st->codecpar->bit_rate = way_bs->frame_size_bytes;*/
	
	st->time_base  = AV_TIME_BASE_Q;
	st->avg_frame_rate=(AVRational){60000,1000};
	/*st->avg_frame_rate=(AVRational){60,1};*/
	/*st->r_frame_rate=(AVRational){60,1};*/

	/*st->frame_duration = av_rescale_q(1, c->time_base, AV_TIME_BASE_Q);*/
	/*st->time_frame = av_gettime_relative();*/

	if(way_bs->frame_format==0)
		st->codecpar->format =AV_PIX_FMT_BGR0;
	else{
		av_log(s, AV_LOG_ERROR, "ragac cudi formatia\n");
		exit(1);
	}

	pthread_create(&frame_thr, NULL, get_frames, (void*)way_bs);
        av_usleep(300*1000);
	av_log(s, AV_LOG_INFO, "wayland is init morcha\n");
	return 0;
}

static void xcbgrab_image_reply_free(void *opaque, uint8_t *data)
{
}


static int wlgrab_read_packet(AVFormatContext *s, AVPacket *pkt)
{
	/*stopwatch_stop_and_print();*/
	/*stopwatch_start();*/
	/*av_log(s,AV_LOG_WARNING,"gib packet\n");*/
	WLGrabContext* way_bs=s->priv_data;

	/*way_bs->frame = zwlr_screencopy_manager_v1_capture_output(way_bs->screencopy_manager, 1, way_bs->output);*/
	/*zwlr_screencopy_frame_v1_add_listener(way_bs->frame, &frame_listener, way_bs);*/
	/*wl_display_dispatch(way_bs->display);*/
	/*// to dispatch the copy*/
	/*wl_display_dispatch(way_bs->display);*/

	/*pkt->dts=pkt->pts=way_bs->pts;*/
	pkt->dts=pkt->pts=av_gettime();
	/*av_log(s,AV_LOG_WARNING,"%lu\n", pkt->pts-way_bs->last_pts);*/

	way_bs->last_pts=pkt->pts;

	pkt->buf = av_buffer_create(way_bs->frame_bytes, way_bs->frame_size_bytes, xcbgrab_image_reply_free, 0, 0);
	pkt->data = way_bs->frame_bytes;
	pkt->size = way_bs->frame_size_bytes;


	return 0;
}
static  int wlgrab_read_close(AVFormatContext *avctx)
{
	av_log(avctx, AV_LOG_ERROR,  "yay sandro\n");
	return 0;
}

const AVInputFormat ff_wlgrab_demuxer = {
	.name           = "wlgrab",
	.long_name      = NULL_IF_CONFIG_SMALL("sandros wayland grabber"),
	.priv_data_size = sizeof(WLGrabContext),
	.read_header    = wlgrab_read_header,
	.read_packet    = wlgrab_read_packet,
	.read_close     = wlgrab_read_close,
	.flags          = AVFMT_NOFILE,
	.priv_class     = &wlgrab_class,
};
