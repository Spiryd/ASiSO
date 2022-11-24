#!/bin/bash
to_print=$'ppid pid comm state tty rss pgid sid \n'
comms=()
states=()
ttys=()
rsss=()
pgids=()
sids=()
ppids=()
pids=()

for pid in $(ls /proc | grep -E '^[0-9]+$')
do
	stat=($(sed -E 's/\([^)]+\)/X/' "/proc/$pid/stat" 2>/dev/null))
	pids+=(${stat[0]})
	ppids+=(${stat[3]})
	states+=(${stat[2]})
	ttys+=(${stat[6]})
	rsss+=(${stat[23]})
	pgids+=(${stat[4]})
	sids+=(${stat[5]})
	comms+=($(echo $(< /proc/$pid/stat) | cut -d " " -f 2))
done

len=${#pids[@]}

for (( i=0; i<$len; i++ ))
do
	to_print+="${ppids[i]} "
	to_print+="${pids[i]} "
	to_print+="${comms[i]} "
	to_print+="${states[i]} "
	to_print+="${ttys[i]} "
	to_print+="${rsss[i]} "
	to_print+="${pgids[i]} "
	to_print+="${sids[i]} "
	to_print+=$'\n'
done

echo "$to_print" | column -t