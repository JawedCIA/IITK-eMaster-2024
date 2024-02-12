#! /bin/sh

res_dir="exe_result/result"
exe_output="exe_result/Task-1"
test_dir="testcases/Task-1"
mkdir -p $exe_output
mkdir -p $res_dir
result="$res_dir/task1_result.txt"
> $result
test(){
  testNo=$1
  testcase=$2
  resActual=$3
  output=$4
  cat $testcase | ./task1_calc > $output
  res=`diff -i $resActual $output | wc -l`
  if [ $res -eq 0 ]
  then
  	echo "TESTCASE-$testNo PASSED" >> $result
  else
  	echo "TESTCASE-$testNo FAILED" >> $result
  fi
}


test 1 $test_dir/test1.csv $test_dir/test1_result.csv $exe_output/r1.csv
test 2 $test_dir/test2.csv $test_dir/test2_result.csv $exe_output/r2.csv
test 3 $test_dir/test3.csv $test_dir/test3_result.csv $exe_output/r3.csv
