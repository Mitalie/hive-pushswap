/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state-ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:48 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/16 15:37:29 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <assert.h>

/*
	forward moves first to last, reverse moves last to first
*/
static void	arr_rot(unsigned char *arr, int size, bool reverse)
{
	unsigned char	tmp;
	int				i;

	if (!reverse)
	{
		i = 0;
		tmp = arr[i];
		while (i++ < size - 1)
			arr[i - 1] = arr[i];
		arr[i - 1] = tmp;
	}
	else
	{
		i = size;
		tmp = arr[i - 1];
		while (--i)
			arr[i] = arr[i - 1];
		arr[i] = tmp;
	}
}

void	sop_r(t_state *s, bool op_a, bool op_b)
{
	assert(op_a || op_b);
	if (op_a)
	{
		assert(s->a < N - s->b);
		arr_rot(s->num, N - s->b, false);
		s->a++;
	}
	if (op_b)
	{
		assert(s->c < s->b);
		arr_rot(s->num + N - s->b, s->b, true);
		s->c++;
	}
}

void	sop_rr(t_state *s, bool op_a, bool op_b)
{
	assert(op_a || op_b);
	if (op_a)
	{
		assert(s->a);
		arr_rot(s->num, N - s->b, true);
		s->a--;
	}
	if (op_b)
	{
		assert(s->c);
		arr_rot(s->num + N - s->b, s->b, false);
		s->c--;
	}
}

void	sop_s(t_state *s, bool op_a, bool op_b)
{
	assert(op_a || op_b);
	if (op_a)
	{
		assert(N - s->a >= 2);
		arr_rot(s->num, 2, false);
	}
	if (op_b)
	{
		assert(s->b - s->c >= 2);
		arr_rot(s->num + N - 2, 2, false);
	}
}

void	sop_p(t_state *s, bool op_a, bool op_b)
{
	assert(op_a != op_b);
	if (op_b)
	{
		assert(N - s->a);
		arr_rot(s->num, N, false);
		s->a++;
		s->b++;
	}
	if (op_a)
	{
		assert(s->b - s->c);
		arr_rot(s->num, N, true);
		s->a--;
		s->b--;
	}
}
