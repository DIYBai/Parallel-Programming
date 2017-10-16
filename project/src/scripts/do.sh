# bash scripts/get_frames.sh

# bash scripts/comp.sh

# bash scripts/time.sh

# cd 12serial_out
# rm *.png
# cd ..
./bin/detect_ser 2input 2serial_out #> ser_fnames.txt
# ./bin/detect_ser 12input 12serial_out #> ser_fnames.txt
./bin/detect_ser 24input 24serial_out #> ser_fnames.txt

# cd 12omp_out
# rm *.png
# cd ..
./bin/detect_omp 2input 2omp_out #> omp_fnames.txt
# ./bin/detect_omp 12input 12omp_out
./bin/detect_omp 24input 24omp_out

# cd 12cilk_out
# rm *.png
# cd ..
./bin/detect_cilk 2input 2cilk_out
# ./bin/detect_cilk 12input 12cilk_out
./bin/detect_cilk 24input 24cilk_out

bash scripts/write_to_video.sh
