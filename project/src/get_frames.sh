cd input
rm *.png
cd ..

#ffmpeg -i input/input.mp4 -vf fps=12 input/in%06d.png
ffmpeg -i input/input.mp4 -vf fps=2 input/in%06d.png
