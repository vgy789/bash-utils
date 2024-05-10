CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c17 -std=c11 -pedantic
OUTPUT_FILE=s21_grep

all: build

build: $(OUTPUT_FILE)

$(OUTPUT_FILE): grep_utility.o regex_list.o error.o
	$(CC) $(CFLAGS) -o $(OUTPUT_FILE) s21_grep.c $^

grep_utility.o:
	$(CC) $(CFLAGS) -c grep_utility.c

regex_list.o:
	$(CC) $(CFLAGS) -c regex_list.c

error.o:
	$(CC) $(CFLAGS) -c ../common/error.c

format:
	clang-format --style=Google -i ./*.{c,h}

clean:
	rm -rf *.o $(OUTPUT_FILE)

rebuild: clean all
