CC=gcc
CFLAGS= -Werror -Wextra -std=c11 -pedantic
OUTPUT_FILE=s21_cat

all: build

build: $(OUTPUT_FILE)

$(OUTPUT_FILE): cat_utility.o platform.o error.o
	$(CC) $(CFLAGS) -o $(OUTPUT_FILE) s21_cat.c $^

cat_utility.o:
	$(CC) $(CFLAGS) -c cat_utility.c

platform.o: error.o
	$(CC) $(CFLAGS) -c platform.c

error.o:
	$(CC) $(CFLAGS) -c error.c

clean:
	rm -rf *.o $(OUTPUT_FILE)

rebuild: clean all
