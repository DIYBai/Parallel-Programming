ffmpeg -r 2 -f image2 -s 1920x1080 -i serial_out/out_in%04d.jpg -vcodec libx264 -crf 25  -pix_fmt yuv420p serial_out/output.mp4
