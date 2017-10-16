cd serial_out
rm *.mp4
cd ..
# ffmpeg -r 2 -f image2 -s 1920x1080 -i input/in%06d.png -vcodec mpeg4 -pix_fmt yuv420p serial_out/OG_output.mp4
# ffmpeg -r 2 -f image2 -s 1920x1080 -i serial_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p serial_out/ser_output.mp4
ffmpeg -r 12 -f image2 -s 1920x1080 -i input/in%06d.png -vcodec mpeg4 -pix_fmt yuv420p serial_out/OG_output.mp4
ffmpeg -r 12 -f image2 -s 1920x1080 -i serial_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p serial_out/ser_output.mp4
# ffmpeg -r 24 -f image2 -s 1920x1080 -i input/in%06d.png -vcodec mpeg4 -pix_fmt yuv420p serial_out/OG_output.mp4
# ffmpeg -r 24 -f image2 -s 1920x1080 -i serial_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p serial_out/ser_output.mp4


cd omp_out
rm *.mp4
cd ..
# ffmpeg -r 2 -f image2 -s 1920x1080 -i omp_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p omp_out/omp_output.mp4
ffmpeg -r 12 -f image2 -s 1920x1080 -i omp_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p omp_out/omp_output.mp4
# ffmpeg -r 24 -f image2 -s 1920x1080 -i omp_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p omp_out/omp_output.mp4

cd cilk_out
rm *.mp4
cd ..
# ffmpeg -r 2 -f image2 -s 1920x1080 -i cilk_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p cilk_out/cilk_output.mp4
ffmpeg -r 12 -f image2 -s 1920x1080 -i cilk_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p cilk_out/cilk_output.mp4
# ffmpeg -r 24 -f image2 -s 1920x1080 -i cilk_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p cilk_out/cilk_output.mp4
