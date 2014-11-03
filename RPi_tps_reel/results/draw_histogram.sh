#! /bin/sh

if [ $# -ne 4 ]
then
	echo "usage: $0 title result-file result-name png-file" >&2
	exit 1
fi

cmd=$(
	printf "set terminal png size 640,480 font 'Arial-Bold' ;"
	printf "set title '%s';" "$1" 
	printf "set logscale x;"
	printf "set logscale y;"
	printf "set border 0;"
	printf "set xlabel 'Retard (µs)';"
	printf "set ylabel 'Occurrences';"
	printf "set arrow from 1,0.09 to 12000,0.09 lw 2;"
	printf "set arrow from 1,0.1 to 1,2000000 lw 2;"
	printf "set xtics nomirror out 10,10;"
	printf "set ytics nomirror out 1,10;"
	printf "plot [x=1:10000][y=0.1:1000000] '%s' title '%s' with boxes linewidth 2;" "$2" "$3"
)

echo $cmd | gnuplot > "$4"

