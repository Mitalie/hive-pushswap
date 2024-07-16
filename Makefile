
TESTS = test-merge cost-radix optimals

$(TESTS): %: %.c
	$(CC) -Wall -Wextra -Werror $(CFLAGS) $^ -o $@

test-merge: util/circ*.c

all: $(TESTS)
