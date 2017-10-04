srun g++ -o stencil_serial serial.cpp -lopencv_core -lopencv_imgcodecs
srun g++ -o stencil_openmp -fopenmp openmp.cpp -lopencv_core -lopencv_imgcodecs
srun g++ -o stencil_openmp2 -fopenmp openmp2.cpp -lopencv_core -lopencv_imgcodecs
srun g++ -o stencil_openmp3 -fopenmp openmp3.cpp -lopencv_core -lopencv_imgcodecs
srun g++ -o stencil_cilk -fcilkplus cilk.cpp -lopencv_core -lopencv_imgcodecs
srun g++ -o stencil_cilk2 -fcilkplus cilk2.cpp -lopencv_core -lopencv_imgcodecs
#srun g++ -o stencil_tbb tbb.cpp -ltbb -lopencv_core -lopencv_imgcodecs
#srun mpic++ -o stencil_mpi mpi.cpp -lopencv_core -lopencv_imgcodecs
