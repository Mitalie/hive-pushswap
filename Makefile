
TESTS = $(addprefix bin/,test-merge test-polyphase-auto cost-radix optimals)

$(TESTS): bin/%: %.c
	@mkdir -p $(@D)
	$(CC) -Wall -Wextra -Werror -g $(CFLAGS) $^ -o $@

bin/test-merge bin/test-polyphase-auto: util/circ*.c
bin/optimals: util/state*.c util/arr_rot.c util/circ*.c util/const*.c
bin/optimals: CFLAGS += -O3

all: $(TESTS)
.DEFAULT_GOAL := all
