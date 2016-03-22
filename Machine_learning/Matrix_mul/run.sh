#!/bin/bash
source ~/.bashrc
source ./config

hadoop fs -put ../data/M.data /adr/person/cuizhigang/matrix/data
input=/adr/person/cuizhigang/matrix/data/M.data
output=/adr/person/cuizhigang/matrix/result
output_offline=../result/result.data
hadoop fs -rmr $output
rm $output_offline
hadoop streaming -input $input \
    -output $output \
	-mapper 'python map.py 300 500' \
	-reducer 'python reduce.py' \
	-file map.py \
	-file reduce.py \
	-jobconf mapred.job.name="matrix" \
	-jobconf mapred.reduce.tasks=200 \
	-jobconf mapred.map.tasks=200
hadoop fs -getmerge $output $output_offline
