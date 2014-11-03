#! /bin/bash

CYCLICTEST=/root/rt-tests/cyclictest


echo -1 > /proc/sys/kernel/sched_rt_runtime_us

COMMON_OPTS="--quiet --mlockall --latency=0 --histogram=10000"

echo "Policy OTHER (1h tests)"

SPECIF_OPTS="--duration=1h --policy=other"
RESULT_PREFIX="results-$(uname -r)-other"
date +"  [%X] setitimer"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS}  > "${RESULT_PREFIX}-setitimer.txt"
date +"  [%X] clock_nanosleep"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS} --nanosleep  > "${RESULT_PREFIX}-clocknanosleep.txt"
date +"  [%X] nanosleep"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS} --nanosleep --system  > "${RESULT_PREFIX}-nanosleep.txt"
echo

echo "Policy FIFO (2h tests)"
SPECIF_OPTS="--duration=2h --policy=fifo --priority=99"
RESULT_PREFIX="results-$(uname -r)-fifo"
date +"  [%X] setitimer"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS}  > "${RESULT_PREFIX}-setitimer.txt"
date +"  [%X] clock_nanosleep"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS} --nanosleep  > "${RESULT_PREFIX}-clocknanosleep.txt"
date +"  [%X] nanosleep"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS} --nanosleep --system  > "${RESULT_PREFIX}-nanosleep.txt"
echo

echo "Policy RR (2h tests)"
SPECIF_OPTS="--duration=2h --policy=rr --priority=99"
RESULT_PREFIX="results-$(uname -r)-rr"
date +"  [%X] setitimer"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS}  > "${RESULT_PREFIX}-setitimer.txt"
date +"  [%X] clock_nanosleep"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS} --nanosleep  > "${RESULT_PREFIX}-clocknanosleep.txt"
date +"  [%X] nanosleep"
"$CYCLICTEST" ${COMMON_OPTS} ${SPECIF_OPTS} --nanosleep --system  > "${RESULT_PREFIX}-nanosleep.txt"
echo



