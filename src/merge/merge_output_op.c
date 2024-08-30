/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_output_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:20:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/30 16:51:24 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_internal.h"
#include <stdbool.h>
#include <stdio.h>

static bool	cancel(t_merge_state *s, t_ps_op op)
{
	if (!circ_len(s->output_queue))
		return (false);
	if ((op == OP_PA && circ_peek_front(s->output_queue) == OP_PB)
		|| (op == OP_PB && circ_peek_front(s->output_queue) == OP_PA))
	{
		circ_pop_front(s->output_queue);
		return (true);
	}
	return (false);
}

typedef enum e_rot_mode
{
	RA_RB,
	RRA_RB,
	RA_RRB,
	RRA_RRB,
	NUM_MODES,
}	t_rot_mode;

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	flush_rotate(t_merge_state *s)
{
	int			ra;
	int			rra;
	int			rb;
	int			rrb;
	int			modes[NUM_MODES];
	t_rot_mode	i;
	t_rot_mode	best;
	int			best_cost;

	ra = s->output_rot_a;
	if (ra < 0)
		ra += circ_len(s->stacks->a);
	rra = circ_len(s->stacks->a) - ra;
	rb = s->output_rot_b;
	if (rb < 0)
		rb += circ_len(s->stacks->b);
	rrb = circ_len(s->stacks->b) - rb;
	modes[RA_RB] = max(ra, rb);
	modes[RRA_RB] = rra + rb;
	modes[RA_RRB] = ra + rrb;
	modes[RRA_RRB] = max(rra, rrb);
	best = 0;
	i = 0;
	while (++i < NUM_MODES)
		if (modes[i] < modes[best])
			best = i;
	if (best == RA_RB || best == RA_RRB)
		rra = 0;
	if (best == RRA_RB || best == RRA_RRB)
		ra = 0;
	if (best == RA_RB || best == RRA_RB)
		rrb = 0;
	if (best == RA_RRB || best == RRA_RRB)
		rb = 0;
	// TODO output ops
}

static bool	rotate(t_merge_state *s, t_ps_op op)
{
	if (op == OP_RA)
		s->output_rot_a++;
	else if (op == OP_RB)
		s->output_rot_b++;
	else if (op == OP_RR)
	{
		s->output_rot_a++;
		s->output_rot_b++;
	}
	else if (op == OP_RRA)
		s->output_rot_a--;
	else if (op == OP_RRB)
		s->output_rot_b--;
	else if (op == OP_RRR)
	{
		s->output_rot_a--;
		s->output_rot_b--;
	}
	else if (op == OP_SA && s->output_rot_a == 0
		|| op == OP_SB && s->output_rot_b == 0)
		return (false);
	else
	{
		flush_rotate(s);
		return (false);
	}
	return (true);
}

static bool	noop(t_merge_state *s, t_ps_op op)
{
	if ((op == OP_RRA && circ_len(s->stacks->a) <= 1)
		|| (op == OP_RRB && circ_len(s->stacks->b) <= 1))
	{
		return (true);
	}
	return (false);
}

void	merge_output_op(t_merge_state *s, t_ps_op op)
{
	if (op == OP_INVALID)
	{
		while (circ_len(s->output_queue))
			printf("%s\n", op_to_string(circ_pop_back(s->output_queue)));
		return ;
	}
	if (noop(s, op))
		return ;
	if (cancel(s, op))
		return ;
	if (rotate(s, op))
		return ;
	if (circ_len(s->output_queue) == s->output_queue_size)
		printf("%s\n", op_to_string(circ_pop_back(s->output_queue)));
	circ_push_front(s->output_queue, op);
}
