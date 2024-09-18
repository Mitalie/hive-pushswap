/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:28:18 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/18 17:57:19 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"
#include <stdbool.h>

// The lookup table indices must match the t_ps_op enum values in ops.h!

static const char		*g_op_strings[NUM_OPS] = {
	"sa",
	"sb",
	"ss",
	"pa",
	"pb",
	"ra",
	"rb",
	"rr",
	"rra",
	"rrb",
	"rrr",
};

static const t_ps_op	g_op_reverse[NUM_OPS] = {
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PB,
	OP_PA,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_RA,
	OP_RB,
	OP_RR,
};

const char	*op_to_string(t_ps_op op)
{
	if (op >= 0 && op < NUM_OPS)
		return (g_op_strings[op]);
	return (0);
}

static bool	str_equal(const char *a, const char *b)
{
	while (*a || *b)
		if (*a++ != *b++)
			return (false);
	return (true);
}

t_ps_op	op_from_string(const char *str)
{
	t_ps_op	op;

	op = 0;
	while (op < NUM_OPS)
	{
		if (str_equal(str, g_op_strings[op]))
			return (op);
		op++;
	}
	return (OP_INVALID);
}

t_ps_op	op_reverse(t_ps_op op)
{
	if (op >= 0 && op < NUM_OPS)
		return (g_op_reverse[op]);
	return (OP_INVALID);
}
