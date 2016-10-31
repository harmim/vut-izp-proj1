CLFAGS=-std=c99 -Wall -Werror -Wextra
CC=gcc
PROJ=proj1
TESTS=./test.sh

.PHONY: main tests clean

main: $(PROJ).c
	$(CC) $(CLFAGS) $(PROJ).c -o $(PROJ)

tests: $(TESTS)
	$(TESTS)

clean:
	rm -rf $(PROJ)

