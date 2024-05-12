#!/bin/bash

OK_MSG="OK"
ERROR_MSG="ERROR"
PROGRAM_PATH="./s21_grep"
status="$OK_MSG"
TEST_DIR=$1

if [ ! -f "$PROGRAM_PATH" ]; then 
	echo "no such file $PROGRAM_PATH"
	exit 1
fi

test_s21_grep() {
	local option="$1"
	local data="$2"
	local grep_output="grep_output.txt"
    local s21_grep_output="s21_grep_output.txt"

	"$PROGRAM_PATH" "$option" "$data" > "$grep_output"
    grep "$option" "$data" > "$s21_grep_output"

	if ! diff -q "$grep_output" "$s21_grep_output" > /dev/null; then
		status="$ERROR_MSG"
	else
		status="$OK_MSG"
	fi

	rm "$grep_output" "$s21_grep_output"

	if [ "$status" == "$OK_MSG" ]; then
        ((successful_tests++))
    else
        ((failed_tests++))
    fi
	echo -e "$status" "$option"
}

for data in "$TEST_DIR"/data[0-9]*; do
	echo "[$data]"
	cat $data > "/dev/null" || continue

	for template in `echo 'hello grep 42 b n adfasdfads "a*c|b*c" "[0-9]\+"' | xargs`; do
		test_s21_grep "-e $template" $data
		test_s21_grep "-e $template -c" $data
		test_s21_grep "$template" $data

		for flag in `echo '-c -v -i -l -n -h -s -o -oi -ov -ov -ol -on -oh -os' | xargs`; do
			test_s21_grep "-e $template $flag" $data
		done

#		for patterns in "$TEST_DIR"/patterns[0-9]*; do
#		echo
#			test_s21_grep "-f $patterns" $data
#		done
	done
	test_s21_grep "'[0-9]\+'" $data
	test_s21_grep "-e hello -e a -e b -e dafsdf -e" $data
	echo
done

echo "Total successful tests: $successful_tests"
echo "Total failed tests: $failed_tests"
