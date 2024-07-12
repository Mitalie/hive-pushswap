
test: test.c
	$(CC) -Wall -Wextra -Werror $(CFLAGS) $^ -o $@
