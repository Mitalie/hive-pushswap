/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-polyphase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:40:04 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/18 19:12:13 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include "util/circ.h"
#include <stdio.h> // printf for printstacks
#include <stdlib.h> // rand for main

typedef struct s_stacks {
	t_circular	a;
	t_circular	b;
}	t_stacks;

/*static void	printstacks(const t_stacks *s, const char *msg)
{
	t_stacks	copy;

	copy = *s;
	if (msg)
		printf("%s:\n", msg);
	printf("a | ");
	while (copy.a.count)
		printf(" %2d", circ_shift(&copy.a));
	printf("\nb | ");
	while (copy.b.count)
		printf(" %2d", circ_shift(&copy.b));
	printf("\n");
}*/

typedef enum e_ppm_next
{
	A1,
	A2,
	B1,
	B2,
	N_PPM_TARGETS
}	t_ppm_curr;

typedef struct s_ppm_state
{
	t_ppm_curr	curr;
	size_t		runs[N_PPM_TARGETS];
	size_t		total_runs;
}	t_ppm_state;

static bool	cmp(int dir, int a, int b)
{
	if (dir < 0)
		return (a < b);
	return (a > b);
}

static size_t	g_op_count = 0;

static void	merge_one_run_ppm(t_circular *c_data, t_circular *o_data, t_circular *c_seg, t_circular *o_seg)
{
	int	n_tb;
	int	n_ot;
	int	n_ob;
	int	dir;

	n_tb = circ_shift(c_seg);
	n_ot = circ_pop(o_seg);
	n_ob = circ_shift(o_seg);
	circ_push(c_seg, n_tb - n_ot + n_ob);
	//printf("merge run %d\n", circ_peek_top(c_seg));
	dir = 1;
	if (circ_peek_top(c_seg) < 0)
		dir = -1;
	while (n_tb || n_ot || n_ob)
	{
		if (n_tb
			&& (!n_ot || cmp(dir, circ_peek_bottom(c_data), circ_peek_top(o_data)))
			&& (!n_ob || cmp(dir, circ_peek_bottom(c_data), circ_peek_bottom(o_data))))
		{
			// rra
			circ_push(c_data, circ_shift(c_data));
			n_tb -= dir;
			g_op_count++;
		}
		else if (n_ot && (!n_ob || cmp(dir, circ_peek_top(o_data), circ_peek_bottom(o_data))))
		{
			// pa
			circ_push(c_data, circ_pop(o_data));
			n_ot += dir;
			g_op_count++;
		}
		else
		{
			// rrb pa
			circ_push(c_data, circ_shift(o_data));
			n_ob -= dir;
			g_op_count++;
			g_op_count++;
		}
	}
}

static void	merge_level_ppm(t_stacks *data, t_stacks *seg, t_ppm_state *state)
{
	t_ppm_curr	prev;
	size_t		i;

	//printf("ops before level: %zu\n", g_op_count);
	state->curr = (state->curr + N_PPM_TARGETS - 1) % N_PPM_TARGETS;
	prev = (state->curr + N_PPM_TARGETS - 1) % N_PPM_TARGETS;
	state->runs[state->curr] = state->runs[prev];
	i = 0;
	while (i < N_PPM_TARGETS)
		if (i++ != state->curr)
			state->runs[i - 1] -= state->runs[state->curr];
	i = state->runs[state->curr];
	if (state->curr == A1 || state->curr == A2)
		while (i--)
			merge_one_run_ppm(&data->a, &data->b, &seg->a, &seg->b);
	else
		while (i--)
			merge_one_run_ppm(&data->b, &data->a, &seg->b, &seg->a);
}

static void	split_one_run_ppm(t_circular *from, t_circular *other)
{
	int		dir;

	dir = circ_pop(from);
	circ_unshift(from, dir);
	circ_push(other, -dir);
	circ_unshift(other, dir);
}

static void	split_level_ppm(t_stacks *seg, t_ppm_state *state)
{
	size_t	i;

	i = 0;
	while (i < N_PPM_TARGETS)
		if (i++ != state->curr)
			state->runs[i - 1] += state->runs[state->curr];
	i = state->runs[state->curr];
	state->total_runs += i * 2;
	state->runs[state->curr] = 0;
	if (state->curr == A1 || state->curr == A2)
		while (i--)
			split_one_run_ppm(&seg->a, &seg->b);
	else
		while (i--)
			split_one_run_ppm(&seg->b, &seg->a);
	state->curr = (state->curr + 1) % N_PPM_TARGETS;
}

static void	balance_stacks_ppm(t_stacks *data, t_stacks *seg)
{
	size_t	delta;
	size_t	i;

	//printf("balance delta: %ld\n", (long)data->a.count - (long)seg->a.count);
	while (data->a.count > seg->a.count)
	{
		// pb
		circ_push(&data->b, circ_pop(&data->a));
		g_op_count++;
	}
	while (data->a.count < seg->a.count)
	{
		// pa
		circ_push(&data->a, circ_pop(&data->b));
		g_op_count++;
	}
	delta = seg->b.count - data->b.count;
	//printf("dummy segments: %zu\n", delta);
	i = delta;
	while (i--)
		circ_shift(&seg->b);
	i = delta;
	while (i--)
		circ_unshift(&seg->b, 0);
}

static void	segment_rec_ppm(t_stacks *data, t_stacks *seg, t_ppm_state *state, size_t n_items)
{
	//printstacks(seg, "runs before split");
	split_level_ppm(seg, state);
	if (state->total_runs < n_items)
		segment_rec_ppm(data, seg, state, n_items);
	else
		balance_stacks_ppm(data, seg);
	//printstacks(seg, "runs before merge");
	//printstacks(data, "data before merge");
	merge_level_ppm(data, seg, state);
}

static void	segment(t_stacks *data, int n_items)
{
	t_stacks	seg;
	t_ppm_state	state;

	circ_init(&seg.a, n_items * 3);
	circ_init(&seg.b, n_items * 3);
	circ_push(&seg.a, 1);
	state = (t_ppm_state){0};
	state.curr = A1;
	state.runs[A1] = 1;
	state.total_runs = 1;
	segment_rec_ppm(data, &seg, &state, n_items);
	circ_deinit(&seg.a);
	circ_deinit(&seg.b);
}

//#define N 5000

int	main(int argc, char **argv)
{
	(void) argc;
	int			N = atoi(argv[1]);
	t_stacks	s;
	int			arr[N];
	int			j;
	int			t;

	circ_init(&s.a, N);
	circ_init(&s.b, N);
	for (int i = 0; i < N; i++)
		arr[i] = i;
	for (int i = 0; i + 1 < N; i++)
	{
		j = i + rand() / (RAND_MAX / (N - i) + 1);
		t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
	}
	for (int i = 0; i < N; i++)
		circ_push(&s.a, arr[i]);
	segment(&s, N);
	printf("%zu\n", g_op_count);
	//printstacks(&s, "data after");
	circ_deinit(&s.a);
	circ_deinit(&s.b);
}
