cd input
rm *.jpg
cd ..
bash get_frames.sh
bash comp.sh
./detect input serial_out
