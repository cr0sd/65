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
dialog --title "$0" --radiolist "Choose make utility" $NV $NH 10 \
	make "" on \
	rake "" off \
	2>$TMPFILE
MAKECMD=$(cat .dialogtmpfile)

# Choose TARGET
dialog --title "$0" --radiolist "Choose target" $NV $NH 10 \
	all "all" on \
	clean "clean" off \
	2>$TMPFILE
TARGET=$(cat .dialogtmpfile)

# Choose multi-threading/jobs options
dialog --title "$0" --radiolist "Choose number of jobs/threads" $NV $NH 10 \
	1 "1 thread (one job at a time)" off \
	2 "2 threads" off \
	4 "4 threads" on \
	8 "8 threads" off \
	2>$TMPFILE
NJOBS=$(cat .dialogtmpfile)

# Confirm build options
dialog --title "$0" --yesno "You chose to build $TARGET with $NJOBS jobs. Is this okay?\n\nPress No to cancel build." $NV $NH
YESNO=$?
if [ $YESNO -eq 0 ]; then
	if [ $MAKECMD = "rake" ]; then JOBSOPT=""; NJOBS=""; fi
	dialog --prgbox "$MAKECMD $TARGET $JOBSOPT $NJOBS" $NV $NH
fi

# Remove temporary file
rm -f $TMPFILE

# 'Clear screen' for niceness
for x in {0..7}; do
	echo ""
done
