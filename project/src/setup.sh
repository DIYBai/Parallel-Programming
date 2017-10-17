module load slurm opencv-3.3.0 gcc-7.2.0 ffmpeg-3.3.4
mkdir 12input bin 12serial_out 12omp_out 12cilk_out video_out

bash scripts/get_frames.sh
bash scripts/comp.sh

# run.sh
