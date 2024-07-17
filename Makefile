
TESTS = $(addprefix bin/,test-merge cost-radix optimals)

$(TESTS): bin/%: %.c
	@mkdir -p $(@D)
	$(CC) -Wall -Wextra -Werror -g $(CFLAGS) $^ -o $@

bin/test-merge: util/circ*.c
bin/optimals: util/state*.c util/arr_rot.c util/circ*.c util/const*.c

all: $(TESTS)
.DEFAULT_GOAL := all
