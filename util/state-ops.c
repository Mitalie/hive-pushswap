/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state-ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:48 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 15:40:02 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <assert.h>
#include "arr_rot.h"

void	sop_r(t_state *s, bool op_a, bool op_b)
{
	assert(op_a || op_b);
	if (op_a)
	{
		assert(N - s->a > 0);
		byte_arr_rot(s->num, N - s->b, false);
		s->a++;
	}
	if (op_b)
	{
		assert(s->b - s->c > 0);
		byte_arr_rot(s->num + N - s->b, s->b, true);
		s->c++;
	}
}

void	sop_rr(t_state *s, bool op_a, bool op_b)
{
	assert(op_a || op_b);
	if (op_a)
	{
		assert(s->a - s->b > 0);
		byte_arr_rot(s->num, N - s->b, true);
		s->a--;
	}
	if (op_b)
	{
		assert(s->c > 0);
		byte_arr_rot(s->num + N - s->b, s->b, false);
		s->c--;
	}
}

void	sop_s(t_state *s, bool op_a, bool op_b)
{
	assert(op_a || op_b);
	if (op_a)
	{
		assert(N - s->a >= 2);
		byte_arr_rot(s->num, 2, false);
	}
	if (op_b)
	{
		assert(s->b - s->c >= 2);
		byte_arr_rot(s->num + N - 2, 2, false);
	}
}

void	sop_p(t_state *s, bool op_a, bool op_b)
{
	assert(op_a != op_b);
	if (op_b)
	{
		assert(N - s->a > 0);
		byte_arr_rot(s->num, N, false);
		s->a++;
		s->b++;
	}
	if (op_a)
	{
		assert(s->b - s->c > 0);
		byte_arr_rot(s->num, N, true);
		s->a--;
		s->b--;
	}
}
