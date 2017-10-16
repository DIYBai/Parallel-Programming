#bash get_frames.sh

bash comp.sh

cd serial_out
rm *.png
cd ..
./detect_ser input serial_out #> ser_fnames.txt

cd omp_out
rm *.png
cd ..
./detect_omp input omp_out #> omp_fnames.txt

cd cilk_out
rm *.png
cd ..
./detect_cilk input cilk_out

bash write_to_video.sh > misc.txt
