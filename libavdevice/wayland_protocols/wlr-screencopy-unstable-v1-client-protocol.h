/* Generated by wayland-scanner 1.19.0 */

#ifndef WLR_SCREENCOPY_UNSTABLE_V1_CLIENT_PROTOCOL_H
#define WLR_SCREENCOPY_UNSTABLE_V1_CLIENT_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @page page_wlr_screencopy_unstable_v1 The wlr_screencopy_unstable_v1 protocol
 * screen content capturing on client buffers
 *
 * @section page_desc_wlr_screencopy_unstable_v1 Description
 *
 * This protocol allows clients to ask the compositor to copy part of the
 * screen content to a client buffer.
 *
 * Warning! The protocol described in this file is experimental and
 * backward incompatible changes may be made. Backward compatible changes
 * may be added together with the corresponding interface version bump.
 * Backward incompatible changes are done by bumping the version number in
 * the protocol and interface names and resetting the interface version.
 * Once the protocol is to be declared stable, the 'z' prefix and the
 * version number in the protocol and interface names are removed and the
 * interface version number is reset.
 *
 * @section page_ifaces_wlr_screencopy_unstable_v1 Interfaces
 * - @subpage page_iface_zwlr_screencopy_manager_v1 - manager to inform clients and begin capturing
 * - @subpage page_iface_zwlr_screencopy_frame_v1 - a frame ready for copy
 * @section page_copyright_wlr_screencopy_unstable_v1 Copyright
 * <pre>
 *
 * Copyright © 2018 Simon Ser
 * Copyright © 2019 Andri Yngvason
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * </pre>
 */
struct wl_buffer;
struct wl_output;
struct zwlr_screencopy_frame_v1;
struct zwlr_screencopy_manager_v1;

#ifndef ZWLR_SCREENCOPY_MANAGER_V1_INTERFACE
#define ZWLR_SCREENCOPY_MANAGER_V1_INTERFACE
/**
 * @page page_iface_zwlr_screencopy_manager_v1 zwlr_screencopy_manager_v1
 * @section page_iface_zwlr_screencopy_manager_v1_desc Description
 *
 * This object is a manager which offers requests to start capturing from a
 * source.
 * @section page_iface_zwlr_screencopy_manager_v1_api API
 * See @ref iface_zwlr_screencopy_manager_v1.
 */
/**
 * @defgroup iface_zwlr_screencopy_manager_v1 The zwlr_screencopy_manager_v1 interface
 *
 * This object is a manager which offers requests to start capturing from a
 * source.
 */
extern const struct wl_interface zwlr_screencopy_manager_v1_interface;
#endif
#ifndef ZWLR_SCREENCOPY_FRAME_V1_INTERFACE
#define ZWLR_SCREENCOPY_FRAME_V1_INTERFACE
/**
 * @page page_iface_zwlr_screencopy_frame_v1 zwlr_screencopy_frame_v1
 * @section page_iface_zwlr_screencopy_frame_v1_desc Description
 *
 * This object represents a single frame.
 *
 * When created, a "buffer" event will be sent. The client will then be able
 * to send a "copy" request. If the capture is successful, the compositor
 * will send a "flags" followed by a "ready" event.
 *
 * If the capture failed, the "failed" event is sent. This can happen anytime
 * before the "ready" event.
 *
 * Once either a "ready" or a "failed" event is received, the client should
 * destroy the frame.
 * @section page_iface_zwlr_screencopy_frame_v1_api API
 * See @ref iface_zwlr_screencopy_frame_v1.
 */
/**
 * @defgroup iface_zwlr_screencopy_frame_v1 The zwlr_screencopy_frame_v1 interface
 *
 * This object represents a single frame.
 *
 * When created, a "buffer" event will be sent. The client will then be able
 * to send a "copy" request. If the capture is successful, the compositor
 * will send a "flags" followed by a "ready" event.
 *
 * If the capture failed, the "failed" event is sent. This can happen anytime
 * before the "ready" event.
 *
 * Once either a "ready" or a "failed" event is received, the client should
 * destroy the frame.
 */
extern const struct wl_interface zwlr_screencopy_frame_v1_interface;
#endif

#define ZWLR_SCREENCOPY_MANAGER_V1_CAPTURE_OUTPUT 0
#define ZWLR_SCREENCOPY_MANAGER_V1_CAPTURE_OUTPUT_REGION 1
#define ZWLR_SCREENCOPY_MANAGER_V1_DESTROY 2


/**
 * @ingroup iface_zwlr_screencopy_manager_v1
 */
#define ZWLR_SCREENCOPY_MANAGER_V1_CAPTURE_OUTPUT_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_screencopy_manager_v1
 */
#define ZWLR_SCREENCOPY_MANAGER_V1_CAPTURE_OUTPUT_REGION_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_screencopy_manager_v1
 */
#define ZWLR_SCREENCOPY_MANAGER_V1_DESTROY_SINCE_VERSION 1

/** @ingroup iface_zwlr_screencopy_manager_v1 */
static inline void
zwlr_screencopy_manager_v1_set_user_data(struct zwlr_screencopy_manager_v1 *zwlr_screencopy_manager_v1, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) zwlr_screencopy_manager_v1, user_data);
}

/** @ingroup iface_zwlr_screencopy_manager_v1 */
static inline void *
zwlr_screencopy_manager_v1_get_user_data(struct zwlr_screencopy_manager_v1 *zwlr_screencopy_manager_v1)
{
	return wl_proxy_get_user_data((struct wl_proxy *) zwlr_screencopy_manager_v1);
}

static inline uint32_t
zwlr_screencopy_manager_v1_get_version(struct zwlr_screencopy_manager_v1 *zwlr_screencopy_manager_v1)
{
	return wl_proxy_get_version((struct wl_proxy *) zwlr_screencopy_manager_v1);
}

/**
 * @ingroup iface_zwlr_screencopy_manager_v1
 *
 * Capture the next frame of an entire output.
 */
static inline struct zwlr_screencopy_frame_v1 *
zwlr_screencopy_manager_v1_capture_output(struct zwlr_screencopy_manager_v1 *zwlr_screencopy_manager_v1, int32_t overlay_cursor, struct wl_output *output)
{
	struct wl_proxy *frame;

	frame = wl_proxy_marshal_constructor((struct wl_proxy *) zwlr_screencopy_manager_v1,
			 ZWLR_SCREENCOPY_MANAGER_V1_CAPTURE_OUTPUT, &zwlr_screencopy_frame_v1_interface, NULL, overlay_cursor, output);

	return (struct zwlr_screencopy_frame_v1 *) frame;
}

/**
 * @ingroup iface_zwlr_screencopy_manager_v1
 *
 * Capture the next frame of an output's region.
 *
 * The region is given in output logical coordinates, see
 * xdg_output.logical_size. The region will be clipped to the output's
 * extents.
 */
static inline struct zwlr_screencopy_frame_v1 *
zwlr_screencopy_manager_v1_capture_output_region(struct zwlr_screencopy_manager_v1 *zwlr_screencopy_manager_v1, int32_t overlay_cursor, struct wl_output *output, int32_t x, int32_t y, int32_t width, int32_t height)
{
	struct wl_proxy *frame;

	frame = wl_proxy_marshal_constructor((struct wl_proxy *) zwlr_screencopy_manager_v1,
			 ZWLR_SCREENCOPY_MANAGER_V1_CAPTURE_OUTPUT_REGION, &zwlr_screencopy_frame_v1_interface, NULL, overlay_cursor, output, x, y, width, height);

	return (struct zwlr_screencopy_frame_v1 *) frame;
}

/**
 * @ingroup iface_zwlr_screencopy_manager_v1
 *
 * All objects created by the manager will still remain valid, until their
 * appropriate destroy request has been called.
 */
static inline void
zwlr_screencopy_manager_v1_destroy(struct zwlr_screencopy_manager_v1 *zwlr_screencopy_manager_v1)
{
	wl_proxy_marshal((struct wl_proxy *) zwlr_screencopy_manager_v1,
			 ZWLR_SCREENCOPY_MANAGER_V1_DESTROY);

	wl_proxy_destroy((struct wl_proxy *) zwlr_screencopy_manager_v1);
}

#ifndef ZWLR_SCREENCOPY_FRAME_V1_ERROR_ENUM
#define ZWLR_SCREENCOPY_FRAME_V1_ERROR_ENUM
enum zwlr_screencopy_frame_v1_error {
	/**
	 * the object has already been used to copy a wl_buffer
	 */
	ZWLR_SCREENCOPY_FRAME_V1_ERROR_ALREADY_USED = 0,
	/**
	 * buffer attributes are invalid
	 */
	ZWLR_SCREENCOPY_FRAME_V1_ERROR_INVALID_BUFFER = 1,
};
#endif /* ZWLR_SCREENCOPY_FRAME_V1_ERROR_ENUM */

#ifndef ZWLR_SCREENCOPY_FRAME_V1_FLAGS_ENUM
#define ZWLR_SCREENCOPY_FRAME_V1_FLAGS_ENUM
enum zwlr_screencopy_frame_v1_flags {
	/**
	 * contents are y-inverted
	 */
	ZWLR_SCREENCOPY_FRAME_V1_FLAGS_Y_INVERT = 1,
};
#endif /* ZWLR_SCREENCOPY_FRAME_V1_FLAGS_ENUM */

/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 * @struct zwlr_screencopy_frame_v1_listener
 */
struct zwlr_screencopy_frame_v1_listener {
	/**
	 * buffer information
	 *
	 * Provides information about the frame's buffer. This event is
	 * sent once as soon as the frame is created.
	 *
	 * The client should then create a buffer with the provided
	 * attributes, and send a "copy" request.
	 * @param format buffer format
	 * @param width buffer width
	 * @param height buffer height
	 * @param stride buffer stride
	 */
	void (*buffer)(void *data,
		       struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1,
		       uint32_t format,
		       uint32_t width,
		       uint32_t height,
		       uint32_t stride);
	/**
	 * frame flags
	 *
	 * Provides flags about the frame. This event is sent once before
	 * the "ready" event.
	 * @param flags frame flags
	 */
	void (*flags)(void *data,
		      struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1,
		      uint32_t flags);
	/**
	 * indicates frame is available for reading
	 *
	 * Called as soon as the frame is copied, indicating it is
	 * available for reading. This event includes the time at which
	 * presentation happened at.
	 *
	 * The timestamp is expressed as tv_sec_hi, tv_sec_lo, tv_nsec
	 * triples, each component being an unsigned 32-bit value. Whole
	 * seconds are in tv_sec which is a 64-bit value combined from
	 * tv_sec_hi and tv_sec_lo, and the additional fractional part in
	 * tv_nsec as nanoseconds. Hence, for valid timestamps tv_nsec must
	 * be in [0, 999999999]. The seconds part may have an arbitrary
	 * offset at start.
	 *
	 * After receiving this event, the client should destroy the
	 * object.
	 * @param tv_sec_hi high 32 bits of the seconds part of the timestamp
	 * @param tv_sec_lo low 32 bits of the seconds part of the timestamp
	 * @param tv_nsec nanoseconds part of the timestamp
	 */
	void (*ready)(void *data,
		      struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1,
		      uint32_t tv_sec_hi,
		      uint32_t tv_sec_lo,
		      uint32_t tv_nsec);
	/**
	 * frame copy failed
	 *
	 * This event indicates that the attempted frame copy has failed.
	 *
	 * After receiving this event, the client should destroy the
	 * object.
	 */
	void (*failed)(void *data,
		       struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1);
	/**
	 * carries the coordinates of the damaged region
	 *
	 * This event is sent right before the ready event when
	 * copy_with_damage is requested. It may be generated multiple
	 * times for each copy_with_damage request.
	 *
	 * The arguments describe a box around an area that has changed
	 * since the last copy request that was derived from the current
	 * screencopy manager instance.
	 *
	 * The union of all regions received between the call to
	 * copy_with_damage and a ready event is the total damage since the
	 * prior ready event.
	 * @param x damaged x coordinates
	 * @param y damaged y coordinates
	 * @param width current width
	 * @param height current height
	 * @since 2
	 */
	void (*damage)(void *data,
		       struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1,
		       uint32_t x,
		       uint32_t y,
		       uint32_t width,
		       uint32_t height);
};

/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
static inline int
zwlr_screencopy_frame_v1_add_listener(struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1,
				      const struct zwlr_screencopy_frame_v1_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) zwlr_screencopy_frame_v1,
				     (void (**)(void)) listener, data);
}

#define ZWLR_SCREENCOPY_FRAME_V1_COPY 0
#define ZWLR_SCREENCOPY_FRAME_V1_DESTROY 1
#define ZWLR_SCREENCOPY_FRAME_V1_COPY_WITH_DAMAGE 2

/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
#define ZWLR_SCREENCOPY_FRAME_V1_BUFFER_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
#define ZWLR_SCREENCOPY_FRAME_V1_FLAGS_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
#define ZWLR_SCREENCOPY_FRAME_V1_READY_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
#define ZWLR_SCREENCOPY_FRAME_V1_FAILED_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
#define ZWLR_SCREENCOPY_FRAME_V1_DAMAGE_SINCE_VERSION 2

/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
#define ZWLR_SCREENCOPY_FRAME_V1_COPY_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
#define ZWLR_SCREENCOPY_FRAME_V1_DESTROY_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 */
#define ZWLR_SCREENCOPY_FRAME_V1_COPY_WITH_DAMAGE_SINCE_VERSION 2

/** @ingroup iface_zwlr_screencopy_frame_v1 */
static inline void
zwlr_screencopy_frame_v1_set_user_data(struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) zwlr_screencopy_frame_v1, user_data);
}

/** @ingroup iface_zwlr_screencopy_frame_v1 */
static inline void *
zwlr_screencopy_frame_v1_get_user_data(struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1)
{
	return wl_proxy_get_user_data((struct wl_proxy *) zwlr_screencopy_frame_v1);
}

static inline uint32_t
zwlr_screencopy_frame_v1_get_version(struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1)
{
	return wl_proxy_get_version((struct wl_proxy *) zwlr_screencopy_frame_v1);
}

/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 *
 * Copy the frame to the supplied buffer. The buffer must have a the
 * correct size, see zwlr_screencopy_frame_v1.buffer. The buffer needs to
 * have a supported format.
 *
 * If the frame is successfully copied, a "flags" and a "ready" events are
 * sent. Otherwise, a "failed" event is sent.
 */
static inline void
zwlr_screencopy_frame_v1_copy(struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1, struct wl_buffer *buffer)
{
	wl_proxy_marshal((struct wl_proxy *) zwlr_screencopy_frame_v1,
			 ZWLR_SCREENCOPY_FRAME_V1_COPY, buffer);
}

/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 *
 * Destroys the frame. This request can be sent at any time by the client.
 */
static inline void
zwlr_screencopy_frame_v1_destroy(struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1)
{
	wl_proxy_marshal((struct wl_proxy *) zwlr_screencopy_frame_v1,
			 ZWLR_SCREENCOPY_FRAME_V1_DESTROY);

	wl_proxy_destroy((struct wl_proxy *) zwlr_screencopy_frame_v1);
}

/**
 * @ingroup iface_zwlr_screencopy_frame_v1
 *
 * Same as copy, except it waits until there is damage to copy.
 */
static inline void
zwlr_screencopy_frame_v1_copy_with_damage(struct zwlr_screencopy_frame_v1 *zwlr_screencopy_frame_v1, struct wl_buffer *buffer)
{
	wl_proxy_marshal((struct wl_proxy *) zwlr_screencopy_frame_v1,
			 ZWLR_SCREENCOPY_FRAME_V1_COPY_WITH_DAMAGE, buffer);
}

#ifdef  __cplusplus
}
#endif

#endif
