set terminal jpeg
set output "chart.jpg"
#set autoscale
set logscale
set xrange[100:100000]
set yrange[.001:13]
set xtics(100, 1000, 10000, 100000)
set xlabel "Heap size (items)"
set ylabel "Time (seconds)"
set title ""
plot "plotData.txt" using 1:2 with lines title "Naive Heapsort",\
"plotData.txt" using 1:3 with lines title "Fibonacci Heapsort"
