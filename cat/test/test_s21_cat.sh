#!/bin/bash

OK_MSG="OK"
ERROR_MSG="FAIL"
PROGRAM_PATH="./s21_cat"
TEST_DIR=$1
status="$OK_MSG"
successful_tests=0
failed_tests=0

if [ ! -f "$PROGRAM_PATH" ]; then 
	echo "no such file $PROGRAM_PATH"
	exit 1
fi

test_s21_cat() {
	local option="$1"
	local file="$2"
	local cat_output="cat_output.txt"
    local s21_cat_output="s21_cat_output.txt"

	"$PROGRAM_PATH" "$option" "$file" "$file" > "$cat_output"
    cat "$option" "$file" "$file" > "$s21_cat_output"

	if ! diff -q "$cat_output" "$s21_cat_output" > /dev/null; then
		status="$ERROR_MSG"
	else
		status="$OK_MSG"
	fi

	rm "$cat_output" "$s21_cat_output"

	if [ "$status" == "$OK_MSG" ]; then
        ((successful_tests++))
    else
        ((failed_tests++))
    fi
	echo -e "$status" "$option"
}

case "$(uname -s)" in
	Linux*)     MACHINE=Linux;;
	Darwin*)    MACHINE=Mac
esac

for file in "$TEST_DIR"/test[0-9]*; do
		echo "[$file]"
		cat $file > "/dev/null" || continue
	for flag in `echo '-b -v -e -n -s -t -bn -nb -te -bs' | xargs`; do
		test_s21_cat "$flag" "$file"
	done

	if [[ $MACHINE == "Linux" ]]; then 
		for flag in `echo '--number-nonblank -T -E -TE --number --squeeze-blank' | xargs`; do
			test_s21_cat "$flag" "$file"
		done
	fi
done

echo "Total successful tests: $successful_tests"
echo "Total failed tests: $failed_tests"
