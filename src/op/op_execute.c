/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:43:36 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/20 17:29:20 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

#include "circ.h"
#include "stacks.h"
#include <stdbool.h>

static void	op_s(t_stacks *s, bool a, bool b)
{
	int	temp1;
	int	temp2;

	if (a && circ_len(s->a) >= 2)
	{
		temp1 = circ_pop_back(s->a);
		temp2 = circ_pop_back(s->a);
		circ_push_back(s->a, temp1);
		circ_push_back(s->a, temp2);
	}
	if (b && circ_len(s->b) >= 2)
	{
		temp1 = circ_pop_back(s->b);
		temp2 = circ_pop_back(s->b);
		circ_push_back(s->b, temp1);
		circ_push_back(s->b, temp2);
	}
}

static void	op_p(t_stacks *s, bool a, bool b)
{
	if (a && circ_len(s->b) >= 1)
		circ_push_back(s->a, circ_pop_back(s->b));
	if (b && circ_len(s->a) >= 1)
		circ_push_back(s->b, circ_pop_back(s->a));
}

static void	op_r(t_stacks *s, bool a, bool b)
{
	if (a && circ_len(s->a) >= 2)
		circ_push_front(s->a, circ_pop_back(s->a));
	if (b && circ_len(s->b) >= 2)
		circ_push_front(s->b, circ_pop_back(s->b));
}

static void	op_rr(t_stacks *s, bool a, bool b)
{
	if (a && circ_len(s->a) >= 2)
		circ_push_back(s->a, circ_pop_front(s->a));
	if (b && circ_len(s->b) >= 2)
		circ_push_back(s->b, circ_pop_front(s->b));
}

void	op_execute(t_stacks *s, t_op op)
{
	if (op == OP_SA)
		op_s(s, true, false);
	else if (op == OP_SB)
		op_s(s, false, true);
	else if (op == OP_SS)
		op_s(s, true, true);
	else if (op == OP_PA)
		op_p(s, true, false);
	else if (op == OP_PB)
		op_p(s, false, true);
	else if (op == OP_RA)
		op_r(s, true, false);
	else if (op == OP_RB)
		op_r(s, false, true);
	else if (op == OP_RR)
		op_r(s, true, true);
	else if (op == OP_RRA)
		op_rr(s, true, false);
	else if (op == OP_RRB)
		op_rr(s, false, true);
	else if (op == OP_RRR)
		op_rr(s, true, true);
}
