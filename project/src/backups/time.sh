#move to src/scripts/

cd 12serial_out
rm *.png
cd ..
./bin/detect_ser 12input 12serial_out
cd 12serial_out
rm *.png
cd ..
./bin/detect_ser 12input 12serial_out

cd 12omp_out
rm *.png
cd ..
./bin/detect_omp 12input 12omp_out
cd 12omp_out
rm *.png
cd ..
./bin/detect_omp 12input 12omp_out

cd 12cilk_out
rm *.png
cd ..
./bin/detect_cilk 12input 12cilk_out
cd 12cilk_out
rm *.png
cd ..
./bin/detect_cilk 12input 12cilk_out
