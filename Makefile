
TESTS = test-merge cost-radix

$(TESTS): %: %.c
	$(CC) -Wall -Wextra -Werror $(CFLAGS) $^ -o $@

test-merge: util/circ*.c

all: $(TESTS)
