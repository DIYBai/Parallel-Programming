cd 2serial_out
rm *.png
cd ..
./bin/detect_ser 2input 2serial_out
cd 2serial_out
rm *.png
cd ..
./bin/detect_ser 2input 2serial_out

cd 2omp_out
rm *.png
cd ..
./bin/detect_omp 2input 2omp_out
cd 2omp_out
rm *.png
cd ..
./bin/detect_omp 2input 2omp_out

cd 2cilk_out
rm *.png
cd ..
./detect_cilk 2input 2cilk_out
cd 2cilk_out
rm *.png
cd ..
./bin/detect_cilk 2input 2cilk_out
