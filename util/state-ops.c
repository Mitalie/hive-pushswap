/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state-ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:48 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 17:54:51 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <assert.h>
#include "arr_rot.h"

bool	sop_r(t_state *s, bool op_a, bool op_b)
{
	if (!op_a && !op_b)
		return (false);
	if (op_a)
	{
		if (N - s->a <= 0)
			return (false);
		byte_arr_rot(s->num, N - s->b, false);
		s->a++;
	}
	if (op_b)
	{
		if (s->b - s->c <= 0)
			return (false);
		byte_arr_rot(s->num + N - s->b, s->b, true);
		s->c++;
	}
	return (true);
}

bool	sop_rr(t_state *s, bool op_a, bool op_b)
{
	if (!op_a && !op_b)
		return (false);
	if (op_a)
	{
		if (s->a - s->b <= 0)
			return (false);
		byte_arr_rot(s->num, N - s->b, true);
		s->a--;
	}
	if (op_b)
	{
		if (s->c <= 0)
			return (false);
		byte_arr_rot(s->num + N - s->b, s->b, false);
		s->c--;
	}
	return (true);
}

bool	sop_s(t_state *s, bool op_a, bool op_b)
{
	if (!op_a && !op_b)
		return (false);
	if (op_a)
	{
		if (N - s->a < 2)
			return (false);
		byte_arr_rot(s->num, 2, false);
	}
	if (op_b)
	{
		if (s->b - s->c < 2)
			return (false);
		byte_arr_rot(s->num + N - 2, 2, false);
	}
	return (true);
}

bool	sop_p(t_state *s, bool op_a, bool op_b)
{
	if (op_a == op_b)
		return (false);
	if (op_b)
	{
		if (N - s->a <= 0)
			return (false);
		byte_arr_rot(s->num, N, false);
		s->a++;
		s->b++;
	}
	if (op_a)
	{
		if (s->b - s->c <= 0)
			return (false);
		byte_arr_rot(s->num, N, true);
		s->a--;
		s->b--;
	}
	return (true);
}

bool	sop(t_state *s, t_sop op)
{
	if (op == SOP_SS)
		return (sop_s(s, true, true));
	else if (op == SOP_SA)
		return (sop_s(s, true, false));
	else if (op == SOP_SB)
		return (sop_s(s, false, true));
	else if (op == SOP_RR)
		return (sop_r(s, true, true));
	else if (op == SOP_RA)
		return (sop_r(s, true, false));
	else if (op == SOP_RB)
		return (sop_r(s, false, true));
	else if (op == SOP_RRR)
		return (sop_rr(s, true, true));
	else if (op == SOP_RRA)
		return (sop_rr(s, true, false));
	else if (op == SOP_RRB)
		return (sop_rr(s, false, true));
	else if (op == SOP_PA)
		return (sop_p(s, true, false));
	else if (op == SOP_PB)
		return (sop_p(s, false, true));
	else
		assert(!"bad op");
	return (false);
}
