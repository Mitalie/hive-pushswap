/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:28:18 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/22 18:28:38 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"
#include <stdbool.h>

static const char	*g_op_strings[NUM_OPS] = {
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
