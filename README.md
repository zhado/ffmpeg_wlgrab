# wlgrab
This is my attempt at building a native wl_roots input device for ffmpeg. It is mostly based on
[wf-recorder](https://github.com/ammen99/wf-recorder) and xcbgrab.c. 

Currently it works on my setup but as I remember getting timestamps right was challenging and video always desynced from audio.

# building
it depends on everything that wf-record and ffmpeg depend on.

after that run :

```bash
$ ./myscript
$ make -j$(nproc)
$ ./ffmpeg -y -f wlgrab -i sandro out.mkv
```
