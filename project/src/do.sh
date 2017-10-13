git reset --hard
git pull

#cd input
#rm *.jpg
#cd ..
#bash get_frames.sh

bash comp.sh
#cd serial_out
#rm *.jpg
#cd ..
./detect_ser input serial_out

#cd omp_out
#rm *.jpg
#cd ..
./detect_omp input omp_out

#cd cilk_out
#rm *.jpg
#cd ..
#./detect_cilk input cilk_out

# cd serial_out
# rm *.mp4
# cd ..
# cd omp_out
# rm *.mp4
# cd ..
# cd cilk_out
# rm *.mp4
# cd ..
# bash write_to_video.sh
