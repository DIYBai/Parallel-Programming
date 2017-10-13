srun g++ -o detect_ser  detect_ser.cpp  -lopencv_core -lopencv_imgcodecs -lopencv_objdetect
srun g++ -o detect_omp  detect_omp.cpp  -lopencv_core -lopencv_imgcodecs -lopencv_objdetect -fopenmp
srun g++ -o detect_cilk detect_cilk.cpp -lopencv_core -lopencv_imgcodecs -lopencv_objdetect -fcilkplus
