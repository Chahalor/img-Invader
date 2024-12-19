#!/bin/bash

# variable
LIST_PID=()
IMG_PATH="tkt.png"
NB_NEW=3

xdg-open $IMG_PATH

LIST_PID+=$(pgrep -n -u "$USER" -f "$IMG_PATH")

while true; do
	for pid in $LIST_PID; do
		# echo "Vérification du processus $pid..."
		if ! ps -p "$pid" > /dev/null 2>&1; then
			# echo "Le processus $pid n'existe plus."
			LIST_PID=($(echo "${LIST_PID[@]/$pid}"))
			xdg-open $IMG_PATH
			for i in $(seq 1 $NB_NEW); do
				xdg-open $IMG_PATH
				LIST_PID+=($(pgrep -n -u "$USER" -f "$IMG_PATH"))
			done
			# LIST_PID+=($(pgrep -n -u "$USER" -f "$IMG_PATH"))
		fi
	done
done
