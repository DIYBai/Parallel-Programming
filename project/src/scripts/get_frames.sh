# cd input #2input, 12input, or 24input
# rm *.png
# cd ..

ffmpeg -i input/input.mp4 -vf fps=2 2input/in%06d.png
ffmpeg -i input/input.mp4 -vf fps=12 12input/in%06d.png
ffmpeg -i input/input.mp4 -vf fps=24 24input/in%06d.png
