#! /bin/sh

PROG=./lecture-temperature.py

uptime
d0=$(date +%s)

while true
do
	d=$(date +%s)
	printf "%d\t" $((d-d0))	
	${PROG}
	sleep 1
done

