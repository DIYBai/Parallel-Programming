cd video_out #2serial_out or 12serial_out or 24serial_out
rm *.mp4
cd ..
# ffmpeg -r 2 -f image2 -s 1920x1080 -i 2input/in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/2OG_output.mp4
# ffmpeg -r 2 -f image2 -s 1920x1080 -i 2serial_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/2ser_output.mp4
ffmpeg -r 12 -f image2 -s 1920x1080 -i 12input/in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/12OG_output.mp4
ffmpeg -r 12 -f image2 -s 1920x1080 -i 12serial_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/12ser_output.mp4
# ffmpeg -r 24 -f image2 -s 1920x1080 -i 24input/in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/24OG_output.mp4
# ffmpeg -r 24 -f image2 -s 1920x1080 -i 24serial_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/24ser_output.mp4


cd 12omp_out
rm *.mp4
cd ..
# ffmpeg -r 2 -f image2 -s 1920x1080 -i 2omp_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/2omp_output.mp4
ffmpeg -r 12 -f image2 -s 1920x1080 -i 12omp_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/12omp_output.mp4
# ffmpeg -r 24 -f image2 -s 1920x1080 -i 24omp_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/24omp_output.mp4

cd 12cilk_out
rm *.mp4
cd ..
# ffmpeg -r 2 -f image2 -s 1920x1080 -i 2cilk_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/2cilk_output.mp4
ffmpeg -r 12 -f image2 -s 1920x1080 -i 12cilk_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/12cilk_output.mp4
# ffmpeg -r 24 -f image2 -s 1920x1080 -i 24cilk_out/out_in%06d.png -vcodec mpeg4 -pix_fmt yuv420p video_out/24cilk_output.mp4
