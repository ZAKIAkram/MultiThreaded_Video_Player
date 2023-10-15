# MultiThreaded_Video_Player
A simple multithreaded video player built using libogg, libtheora, and libvorbis, with SDL2 for rendering and audio.

## Compilation

```sh
cd build
cmake ..
make
make check
make test
```
## Threads

- Main thread: Handles SDL initialization.
- Video thread: Reads and decodes video.
- Audio thread: Reads and decodes audio.
- Display thread: Displays video frames.



