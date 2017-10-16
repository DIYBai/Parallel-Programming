srun g++ -o ../bin/detect_ser  detect_ser.cpp  -lopencv_core -lopencv_imgcodecs -lopencv_objdetect
srun g++ -o ../bin/detect_omp  detect_omp.cpp  -lopencv_core -lopencv_imgcodecs -lopencv_objdetect -fopenmp
srun g++ -o ../bin/detect_cilk detect_cilk.cpp -lopencv_core -lopencv_imgcodecs -lopencv_objdetect -fcilkplus
