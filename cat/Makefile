CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -std=c17 -pedantic
OUTPUT_FILE=s21_cat
TEST_DIR=./test

all: build

build: $(OUTPUT_FILE)

$(OUTPUT_FILE): cat_utility.o error.o
	$(CC) $(CFLAGS) -o $(OUTPUT_FILE) s21_cat.c $^

cat_utility.o:
	$(CC) $(CFLAGS) -c cat_utility.c

error.o:
	$(CC) $(CFLAGS) -c ../common/error.c

test: rebuild
	cp $(OUTPUT_FILE) $(TEST_DIR)
	bash $(TEST_DIR)/test_s21_cat.sh $(TEST_DIR)

format:
	clang-format --style=Google -i ./*.{c,h}

clean:
	rm -rf *.o $(OUTPUT_FILE) $(TEST_DIR)/$(OUTPUT_FILE)

rebuild: clean all
