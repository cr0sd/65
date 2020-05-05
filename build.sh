#!/bin/bash

# Build/UI options
NV=20
NH=50
TMPFILE=._buildconfig
NJOBS=4
TARGET="all"
JOBSOPT="-j"

# Check if dialog is found on system
if [ $(which dialog > /dev/null) -ne 0 ]; then
	echo "$0: error: could not find dialog."
fi

# Choose make vs. rake
dialog --title "Make utility" --radiolist "Choose make utility" $NV $NH 10 \
	make "" on \
	rake "" off \
	2>$TMPFILE
MAKECMD=$(cat $TMPFILE)

# Choose TARGET
dialog --title "Target" --radiolist "Choose target" $NV $NH 10 \
	all "all" on \
	clean "clean" off \
	2>$TMPFILE
TARGET=$(cat $TMPFILE)

# Choose multi-threading/jobs options
if [ $MAKECMD = "make" ]; then
	dialog --title "Jobs/Threads" --radiolist "Choose number of jobs/threads" $NV $NH 10 \
		1 "1 thread (one job at a time)" off \
		2 "2 threads" off \
		4 "4 threads" on \
		8 "8 threads" off \
		2>$TMPFILE
	NJOBS=$(cat $TMPFILE)
fi

# Confirm build options
dialog --title "Confirm" --yesno "You chose to build $TARGET with $NJOBS jobs. Is this okay?\n\nPress No to cancel build." $NV $NH
YESNO=$?
if [ $YESNO -eq 0 ]; then
	if [ $MAKECMD = "rake" ]; then JOBSOPT=""; NJOBS=""; fi
	dialog --title "Building target" --prgbox "$MAKECMD $TARGET $JOBSOPT $NJOBS" $NV $NH
fi

# Remove temporary file
rm -f $TMPFILE

# 'Clear screen' for niceness
for x in {0..7}; do
	echo ""
done
