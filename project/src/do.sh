git reset --hard
git pull

cd input
rm *.jpg
cd ..
bash get_frames.sh

bash comp.sh
cd serial_out
rm *.jpg
cd ..
./detect_ser input serial_out

cd serial_out
rm *.mp4
cd ..
bash write_to_video.sh
