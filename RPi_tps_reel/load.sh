#! /bin/bash

FILE="load.pid"
SERVER=192.168.3.1


echo "Remove $FILE file to stop the process $0."
echo $$ > "$FILE"

while [ -f "$FILE" ]
do
	DURATION=$((15 + $RANDOM % 11))
	/usr/xenomai/bin/dohell -s ${SERVER} -m /run ${DURATION}
	sleep $((30 - ${DURATION}))
done >/dev/null 2>&1 &

