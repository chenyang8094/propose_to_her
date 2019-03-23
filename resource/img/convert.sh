for i in *.gif
do
  convert -resize 64x64 $i `basename $i .gif`.gif_c
done
