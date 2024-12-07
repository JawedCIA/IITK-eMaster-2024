#!/bin/bash

actual_size=0
calculated_size=0

find_actual_size()
{
	output=$(du -bslL $1)
	actual_size=$(echo $output | cut -d ' ' -f 1)
}

find_calculated_size()
{
	calculated_size=$(./myDU $1)
}

if [ ! -f myDU ]
then
	echo "myDU doesn't exist"
	exit -1
fi


#Testcase 1

find_actual_size testcases/Task-3/Testcase1/Root
find_calculated_size testcases/Task-3/Testcase1/Root
echo "Expected output: $actual_size"
echo "Your output: $calculated_size"

if [ $actual_size != "$calculated_size" ]
then
	echo "Testcase 1 failed"
else
	echo "Testcase 1 passed"
fi



#Testcase 2

find_actual_size testcases/Task-3/Testcase2/Root
find_calculated_size testcases/Task-3/Testcase2/Root
echo ""
echo "Expected output: $actual_size"
echo "Your output: $calculated_size"

if [ $actual_size != "$calculated_size" ]
then
	echo "Testcase 2 failed"
else
	echo "Testcase 2 passed"
fi



#Testcase 3

find_actual_size testcases/Task-3/Testcase3/Root
find_calculated_size testcases/Task-3/Testcase3/Root
echo ""
echo "Expected output: $actual_size"
echo "Your output: $calculated_size"

if [ $actual_size != "$calculated_size" ]
then
	echo "Testcase 3 failed"
else
	echo "Testcase 3 passed"
fi

#Testcase 4

CWD=`pwd`
cd testcases/Task-3/Testcase4/Root
rm sym_link
ln -s ../../dummy_root/ sym_link
cd $CWD
find_actual_size testcases/Task-3/Testcase4/Root
find_calculated_size testcases/Task-3/Testcase4/Root
echo "Expected output: $actual_size"
echo "Your output: $calculated_size"

if [ $actual_size != "$calculated_size" ]
then
	echo "Testcase 4 failed"
else
	echo "Testcase 4 passed"
fi
