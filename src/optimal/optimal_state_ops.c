/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_state_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:11:03 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/20 15:15:29 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal_internal.h"

#include "util.h"

static bool	state_op_s(t_opt_state_arr *s, bool a, bool b)
{
	bool	do_a;
	bool	do_b;

	do_a = (a && s->num_a >= 2);
	do_b = (b && s->num_b >= 2);
	if (do_a)
		util_int_arr_rot_one(s->items + s->num_b, 2, false);
	if (do_b)
		util_int_arr_rot_one(s->items + s->num_b - 2, 2, false);
	return (do_a || do_b);
}

static bool	state_op_p(t_opt_state_arr *s, bool a, bool b)
{
	if (a && s->num_b)
	{
		s->num_a++;
		s->num_b--;
	}
	else if (b && s->num_a)
	{
		s->num_a--;
		s->num_b++;
	}
	else
		return (false);
	return (true);
}

static bool	state_op_r(t_opt_state_arr *s, bool a, bool b)
{
	bool	do_a;
	bool	do_b;

	do_a = (a && s->num_a >= 2);
	do_b = (b && s->num_b >= 2);
	if (do_a)
		util_int_arr_rot_one(s->items + s->num_b, s->num_a, false);
	if (do_b)
		util_int_arr_rot_one(s->items, s->num_b, true);
	return (do_a || do_b);
}

static bool	state_op_rr(t_opt_state_arr *s, bool a, bool b)
{
	bool	do_a;
	bool	do_b;

	do_a = (a && s->num_a >= 2);
	do_b = (b && s->num_b >= 2);
	if (do_a)
		util_int_arr_rot_one(s->items + s->num_b, s->num_a, true);
	if (do_b)
		util_int_arr_rot_one(s->items, s->num_b, false);
	return (do_a || do_b);
}

/*
	Perform an operation on the state. Returns true if the state was changed,
	false if the op changes nothing in current state.
*/
bool	optimal_state_op(t_opt_state_arr *s, t_op op)
{
	if (op == OP_SA)
		return (state_op_s(s, true, false));
	else if (op == OP_SB)
		return (state_op_s(s, false, true));
	else if (op == OP_SS)
		return (state_op_s(s, true, true));
	else if (op == OP_PA)
		return (state_op_p(s, true, false));
	else if (op == OP_PB)
		return (state_op_p(s, false, true));
	else if (op == OP_RA)
		return (state_op_r(s, true, false));
	else if (op == OP_RB)
		return (state_op_r(s, false, true));
	else if (op == OP_RR)
		return (state_op_r(s, true, true));
	else if (op == OP_RRA)
		return (state_op_rr(s, true, false));
	else if (op == OP_RRB)
		return (state_op_rr(s, false, true));
	else if (op == OP_RRR)
		return (state_op_rr(s, true, true));
	else
		return (false);
}
