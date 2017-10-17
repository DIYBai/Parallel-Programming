From this directory, just type "bash setup.sh" to set up everything. "setup.sh" also
runs the "run.sh" file, though that file can be run on its own to rerun the program.
The last line of run.sh can be commented out if only the frame-processing is desired.

Resulting .mp4 videos will be in ./video_out, while output frames will be in
different folders depending on which implementation. (ex: ./12serial_out)

If you want to test a different video, it must be called "input.mp4" and be placed
in ./input/ (or change the "get_frames.sh" script to take in whatever source .mp4)
