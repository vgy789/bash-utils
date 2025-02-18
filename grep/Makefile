CC = gcc -std=c11
CFLAGS = -Wall -Werror -Wextra -pedantic

OUTPUT_FILE = s21_grep
TEST_DIR = ./tests

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

clean:
	rm -rf *.o $(OUTPUT_FILE) $(TEST_DIR)/$(OUTPUT_FILE)

rebuild: clean all

test: rebuild
	cp $(OUTPUT_FILE) $(TEST_DIR)
	bash $(TEST_DIR)/test_s21_grep.sh $(TEST_DIR)

format:
	clang-format -style='{InsertBraces: true, InsertNewlineAtEOF: true, CommentPragmas: Insert, BasedOnStyle: Google}' *.c *.h -i
