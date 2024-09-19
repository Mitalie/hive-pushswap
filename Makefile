# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 15:34:04 by amakinen          #+#    #+#              #
#    Updated: 2024/09/19 17:18:39 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := push_swap
BONUS := checker

# Directories
OBJDIR := obj
SRCDIR := src

# Project files and targets
SRCS_S := $(addprefix $(SRCDIR)/,\
	circ/circ_basic.c \
	circ/circ_pushpop.c \
	ops/ops.c \
	ops/ops_util.c \
	util/parse_int.c \
	stacks/stacks.c \
)

SRCS_M := $(addprefix $(SRCDIR)/,\
	push_swap_main.c \
	optimal/optimal.c \
	optimal/optimal_graph_search.c \
	optimal/optimal_state_enc.c \
	optimal/optimal_state_ops.c \
	util/arr_rot.c \
	util/factorial.c \
	merge/runs/runs.c \
	merge/runs/runs_populate.c \
	merge/runs/runs_cost.c \
	merge/merge.c \
	merge/merge_run.c \
	merge/merge_op_queue.c \
	ops/write_op.c \
)

SRCS_B := $(addprefix $(SRCDIR)/,\
	checker_main_bonus.c \
	ops/read_ops.c \
)

OBJS_S := $(SRCS_S:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_M := $(SRCS_M:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_B := $(SRCS_B:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS += $(OBJS_S) $(OBJS_M) $(OBJS_B)
BINS += $(NAME) $(BONUS)
$(NAME): $(OBJS_S) $(OBJS_M)
$(BONUS): $(OBJS_S) $(OBJS_B)

# Generic utility targets
.DEFAULT_GOAL := all

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(BINS)

re: fclean all

bonus: $(BONUS)

# Default compiler flags that apply to all targets
def_CFLAGS := -Wall -Wextra -Werror
def_CPPFLAGS := -MMD -MP -I include

# Add sanitizer flags if requested
ifneq (,$(strip $(SANITIZE)))
	def_CFLAGS += -g -fsanitize=$(SANITIZE)
	def_LDFLAGS += -g -fsanitize=$(SANITIZE)
endif

# Combine default def_FLAGS, target specific tgt_FLAGS and user-supplied FLAGS
# into one _FLAGS variable to be used in recipes
flagvars = CFLAGS CPPFLAGS LDFLAGS LDLIBS
$(foreach v,$(flagvars),$(eval _$v := $$(strip $$(def_$v) $$(tgt_$v) $$($v))))

# Recipe command to ensure directory for target exists
mktargetdir = @mkdir -p $(@D)

# Default recipes for each type of target
$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(mktargetdir)
	$(CC) $(_CPPFLAGS) $(_CFLAGS) -c $< -o $@

$(BINS):
	$(mktargetdir)
	$(CC) $(_LDFLAGS) $^ $(_LDLIBS) -o $@

# Inform make that object files don't need to be remade if the requested
# targets are up to date with respect to the source files.
.SECONDARY: $(OBJS)

# Dependency files to handle #include dependencies
DEPS = $(OBJS:.o=.d)
-include $(DEPS)
