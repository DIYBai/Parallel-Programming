git reset --hard
git pull
cd input
rm *.jpg
cd ..
bash get_frames.sh
bash comp.sh
./detect_ser input serial_out
