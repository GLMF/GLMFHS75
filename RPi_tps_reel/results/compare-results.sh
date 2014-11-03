#! /bin/bash

if [ $# -lt 4 ]
then
	echo "usage: $0 title {result-file result-name}... png-file" >&2
	exit 1
fi


plot=0
eval file=\${$#}

cmd=$(
	printf "set terminal png size 640,480 font 'Arial-Bold' ;"
	printf "set title '%s';" "$1"
	shift
	printf 'set logscale y;'
	printf 'set logscale x;'
	printf "set border 0;"
	printf "set xlabel 'Retard (µs)';"
	printf "set ylabel 'Occurrences';"
	printf "set arrow from 10,0.09 to 12000,0.09 lw 2;"
	printf "set arrow from 10,0.1 to 10,20000000 lw 2;"
	printf "set xtics nomirror out 10,10;"
	printf "set ytics nomirror out 1,10;"
	printf 'set multiplot;'

	while [ $# -gt 1 ]
	do
		if [ $plot -eq 0 ]
		then
			plot=1
			printf "plot [x=10:10000] [y=0.1:10000000] "
		else
			printf "replot "
		fi
		printf "'%s' with lines linewidth 2  title '%s';" "$1" "$2"
		shift
		shift
	done
	printf 'unset multiplot;'
)
echo "$cmd" | gnuplot > "$file"
