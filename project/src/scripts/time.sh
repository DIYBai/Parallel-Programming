cd 2serial_out
rm *.png
cd ..
./detect_ser input serial_out
cd 2serial_out
rm *.png
cd ..
./detect_ser input serial_out

cd 2omp_out
rm *.png
cd ..
./detect_omp input omp_out
cd 2omp_out
rm *.png
cd ..
./detect_omp input omp_out

cd 2cilk_out
rm *.png
cd ..
./detect_cilk input cilk_out
cd 2cilk_out
rm *.png
cd ..
./detect_cilk input cilk_out
