/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:32:43 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/09 16:25:29 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge_internal.h"
#include <stdbool.h>
#include <stdio.h>

static int	peek(t_merge_state *s, t_merge_source src)
{
	if (src == CURR_BOT)
		return (circ_peek_front(s->data_curr));
	if (src == OTHER_TOP)
		return (circ_peek_back(s->data_other));
	return (circ_peek_front(s->data_other));
}

static int	pop(t_merge_state *s, t_merge_source src)
{
	s->run_items[src]--;
	if (src == CURR_BOT)
		return (circ_pop_front(s->data_curr));
	if (src == OTHER_TOP)
		return (circ_pop_back(s->data_other));
	return (circ_pop_front(s->data_other));
}

static bool	cmp(t_merge_state *s, t_merge_source a, t_merge_source b)
{
	if (!s->run_items[a])
		return (false);
	if (!s->run_items[b])
		return (true);
	if (s->run_dir < 0)
		return (peek(s, a) < peek(s, b));
	return (peek(s, a) > peek(s, b));
}

static void	init_merge_run(t_merge_state *s)
{
	int	combined;
	int	dir;

	combined = circ_peek_front(s->runs_curr) - circ_peek_back(s->runs_other)
		+ circ_peek_front(s->runs_other);
	dir = 1;
	if (combined < 0)
		dir = -1;
	s->run_items[CURR_BOT] = dir * circ_pop_front(s->runs_curr);
	s->run_items[OTHER_TOP] = -dir * circ_pop_back(s->runs_other);
	s->run_items[OTHER_BOT] = dir * circ_pop_front(s->runs_other);
	circ_push_back(s->runs_curr, combined);
	s->total_run_items = dir * combined;
	s->run_dir = dir;
}

void	merge_run(t_merge_state *s)
{
	t_merge_source	src;

	init_merge_run(s);
	while (s->total_run_items--)
	{
		if (cmp(s, CURR_BOT, OTHER_TOP) && cmp(s, CURR_BOT, OTHER_BOT))
			src = CURR_BOT;
		else if (cmp(s, OTHER_TOP, OTHER_BOT))
			src = OTHER_TOP;
		else
			src = OTHER_BOT;
		circ_push_back(s->data_curr, pop(s, src));
		printf("%s\n", s->pushswap_ops[src]);
	}
}
