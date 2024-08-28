# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 15:34:04 by amakinen          #+#    #+#              #
#    Updated: 2024/08/28 18:24:59 by amakinen         ###   ########.fr        #
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
	circ/circ_ops.c \
	util/parse_int.c \
	stacks/stacks.c \
	ops/ops_string.c \
)

SRCS_M := $(addprefix $(SRCDIR)/,\
	push_swap_main.c \
	runs/runs.c \
	runs/runs_populate.c \
	runs/runs_cost.c \
	merge/merge.c \
	merge/merge_run.c \
	merge/merge_output_op.c \
)

SRCS_B := $(addprefix $(SRCDIR)/,\
	checker_main_bonus.c \
	ops/ops.c \
	read_ops/read_ops.c \
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
