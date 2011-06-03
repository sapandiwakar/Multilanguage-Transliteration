#!/bin/bash
#me_start=`date +%s`


#time_end=`date +%s`
#time_exec=`$(( $time_end-$time_start ))`

#echo "Execution time is $time_exec seconds"

START=$(date +%s%N)
# do something

# start your script work here
./a.out hin_sent_2.rin
# your logic ends here

	END=$(date +%s%N)
	DIFF=$(( $END - $START ))
	echo "It took $DIFF seconds"
