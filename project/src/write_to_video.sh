ffmpeg -r 2 -f image2 -s 1920x1080 -i input/in%06d.jpg -vcodec mpeg4 -pix_fmt yuv420p serial_out/OG_output.mp4
ffmpeg -r 2 -f image2 -s 1920x1080 -i serial_out/out_in%06d.jpg -vcodec mpeg4 -pix_fmt yuv420p serial_out/ser_output.mp4
