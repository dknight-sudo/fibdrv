reset
set ylabel 'time(ns)'
set title 'fib alogo cmp'
set key left top
set term png enhanced font 'Verdana,10'
set output 'exp1.png'
plot [2:93][:] \
'ex.out' using 1:2 with linespoints linewidth 2 title "fib sequence",\
'' using 1:3 with linespoints linewidth 2 title "fast_doubling",\
