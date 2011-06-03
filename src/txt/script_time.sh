#!/bin/bash
#me_start=`date +%s`


START=$(date +%s%N)
# do something

# start your script work here
./transliteration --input_file=in --output_file=out1 --to_convert=hin --tlang=pan
# your logic ends here

	END=$(date +%s%N)
	DIFF=$(( $END - $START ))
	echo "It took $DIFF seconds for wx to utf8"

