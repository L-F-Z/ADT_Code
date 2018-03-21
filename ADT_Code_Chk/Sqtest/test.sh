#!/bin/bash
cnt=0
while true; do
    ./makeData
    ./seqTest
	flag=true
    if diff State.txt stdState.txt; then
        if diff ans.txt stdans.txt;then
			if diff version0.txt versionStd0.txt;then
				if diff version1.txt versionStd1.txt;then
					flag=false
					((cnt++))
				fi
			fi
		fi
	fi
	if ${flag};then
		echo WA
		exit 0
	fi
	echo AC:${cnt}
done
