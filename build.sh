#!/bin/bash

# Build/UI options
NV=20
NH=50
TMPFILE=._buildconfig
NJOBS=4
TARGET="all"
JOBSOPT="-j"
CPULIMOPT=""
CPULIM=""
OTHEROPTS=""

# Die command
die() { echo $1; exit; }

# Check if dialog is found on system
which dialog 2> /dev/null || die "error: could not find dialog"

# Choose make vs. rake
dialog --title "Make utility" --radiolist "Choose make utility" $NV $NH 10 \
	make "" on \
	rake "" off \
	2>$TMPFILE
MAKECMD=$(cat $TMPFILE)

# Choose TARGET
dialog --title "Target" --radiolist "Choose target" $NV $NH 10 \
	all "Build normal target" on \
	clean "Remove binary files" off \
	2>$TMPFILE
TARGET=$(cat $TMPFILE)

# Make utility specific
if [ $MAKECMD = "make" ]; then

	# MAKE SPECIFIC -----
	# Choose multi-threading/jobs options
	dialog --title "Jobs/Threads" --radiolist "Choose number of jobs/threads" $NV $NH 10 \
		1 "1 thread (one job at a time)" off \
		2 "2 threads" off \
		4 "4 threads" on \
		8 "8 threads" off \
		Infinite "No limit" off \
		CPU "Limit by CPU load..." off \
		2>$TMPFILE
	NJOBS=$(cat $TMPFILE)

	# Specify CPU load option if chosen
	if [ $NJOBS = "CPU" ]; then

		# Do infinite jobs (limit only by CPU load)
		NJOBS=""
		#JOBSOPT="-j"

		# Get CPU load limit, validate input
		while true; do
			# Choose CPU load limit
			dialog --title "CPU Load Limit" --inputbox "Choose CPU load limit for make$WARN" $NV $NH "1.0" 2> $TMPFILE
			CPULIM=$(cat $TMPFILE)
			if [[ $CPULIM =~ ^[0-9]*[\.]?[0-9]+$ ]]; then break; fi
			WARN="\n\nInvalid. Please enter valid CPU load (e.g., 1.0, 2.5, ...)"
		done

		CPULIMOPT="-l"
	fi

	# Force build?
	dialog --title "Build only modified files" --yesno "Build only modified source files? This will not rebuild if project is already built." $NV $NH
	YESNO=$?
	if [ $YESNO -eq 1 ]; then
		OTHEROPTS="$OTHEROPTS -B"
	fi

else

	# RAKE SPECIFIC -----
	JOBSOPT=""
	NJOBS=""
	CPULIM=""
	CPULIMOPT=""
fi

# Confirm build options
if [ $MAKECMD = "make" ]; then
	dialog --title "Confirm" --yesno "You chose to build $TARGET with $NJOBS jobs with $MAKECMD. Is this okay?\n\nPress No to cancel build." $NV $NH
else
	# Don't mention NJOBS
	dialog --title "Confirm" --yesno "You chose to build $TARGET with $MAKECMD. Is this okay?\n\nPress No to cancel build." $NV $NH
fi

# Build project
YESNO=$?
if [ $YESNO -eq 0 ]; then

	dialog --title "Building target" \
		--prgbox "$MAKECMD $TARGET $JOBSOPT $NJOBS $CPULIMOPT $CPULIM $OTHEROPTS; echo 'Done.'" $NV $NH
fi

# Remove temporary file
rm -f $TMPFILE

# 'Clear screen' for niceness
for x in {0..7}; do
	echo ""
done
