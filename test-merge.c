/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-merge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:50:52 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/15 12:31:07 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include "util/circ.h"

typedef struct s_stacks {
	t_circular	a;
	t_circular	b;
}	t_stacks;

/*
static void	op_sa(t_stacks *s)
{
	circ_swap_top(&s->a);
}

static void	op_sb(t_stacks *s)
{
	circ_swap_top(&s->b);
}

static void	op_ss(t_stacks *s)
{
	circ_swap_top(&s->a);
	circ_swap_top(&s->b);
}

static void	op_pa(t_stacks *s)
{
	circ_push(&s->a, circ_pop(&s->b));
}

static void	op_pb(t_stacks *s)
{
	circ_push(&s->b, circ_pop(&s->a));
}

static void	op_ra(t_stacks *s)
{
	circ_rotate(&s->a);
}

static void	op_rb(t_stacks *s)
{
	circ_rotate(&s->b);
}

static void	op_rr(t_stacks *s)
{
	circ_rotate(&s->a);
	circ_rotate(&s->b);
}

static void	op_rra(t_stacks *s)
{
	circ_revrotate(&s->a);
}

static void	op_rrb(t_stacks *s)
{
	circ_revrotate(&s->b);
}

static void	op_rrr(t_stacks *s)
{
	circ_revrotate(&s->a);
	circ_revrotate(&s->b);
}

typedef enum e_op {
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
}	t_op;

static void	op(t_stacks *s, t_op op)
{
	if (op == OP_SA)
		op_sa(s);
	else if (op == OP_SB)
		op_sb(s);
	else if (op == OP_SS)
		op_ss(s);
	else if (op == OP_PA)
		op_pa(s);
	else if (op == OP_PB)
		op_pb(s);
	else if (op == OP_RA)
		op_ra(s);
	else if (op == OP_RB)
		op_rb(s);
	else if (op == OP_RR)
		op_rr(s);
	else if (op == OP_RRA)
		op_rra(s);
	else if (op == OP_RRB)
		op_rrb(s);
	else if (op == OP_RRR)
		op_rrr(s);
	else
		assert(!"Invalid op");
}
*/

#include <stdio.h>

#define VERTICAL 0

static void	printstacks(const t_circular *a, const t_circular *b, const char *msg)
{
	t_circular	aa;
	t_circular	bb;

	aa = *a;
	bb = *b;
	if (msg)
		printf("%s:\n", msg);
	if (VERTICAL)
	{
		while (aa.count > bb.count)
			printf(" %2d\n", circ_pop(&aa));
		while (bb.count > aa.count)
			printf("    %2d\n", circ_pop(&bb));
		while (aa.count)
			printf(" %2d %2d\n", circ_pop(&aa), circ_pop(&bb));
		printf("========\n  a  b\n\n");
	}
	else
	{
		printf("a | ");
		while (aa.count)
			printf(" %2d", circ_pop(&aa));
		printf("\nb | ");
		while (bb.count)
			printf(" %2d", circ_pop(&bb));
		printf("\n");
	}
}

static bool	g_flip = false;

static void	printstacks_flipped(t_circular *current, t_circular *other, const char *msg)
{
	if (g_flip)
		printstacks(other, current, msg);
	else
		printstacks(current, other, msg);
}

/*
	Due to the double stack layout, the higher level three-way merges need both
	ascending and descending runs. We must run a top down merge sort that
	determines the required direction of lower level runs before merging. We can
	use similar double stack structure to keep track of this information.
	Positive N in the segment stacks indicates a descending run of length N, and
	negative N indicates an ascending run of length -N. Zero is used as a
	separator between different levels of split/merge.

	Final goal is to have highest value at the bottom of stack A, let's call
	this descending order as the largest value is pushed to the stack first.
	Special case the final merge here: N descending on top of A is created from
	* (N+2)/3 descending on bottom of A
	* (N+1)/3 ascending on top of B
	* N/3 descending on bottom of B
*/

static void	split_one_run(t_circular *from, t_circular *other);
static void	merge_one_run(t_circular *target, t_circular *other, int run);
static void	merge_level(t_circular *c_stack, t_circular *o_stack, t_circular *c_segs, t_circular *o_segs);
static void	segment_rec(t_circular *c_stack, t_circular *o_stack, t_circular *current, t_circular *other, int max_len);

static void	segment(t_stacks *s, t_circular *a, t_circular *b, int n_items)
{
	circ_init(a, n_items);
	circ_init(b, n_items);
	circ_push(a, n_items);
	//printstacks(a, b, "init");
	split_one_run(a, b);
	//printstacks(a, b, "first split");
	segment_rec(&s->a, &s->b, a, b, (n_items + 2) / 3);
	merge_one_run(&s->a, &s->b, n_items);
}

/*
	Our merge strategy is as follows:
	* Run groups are ABC on current stack, DEFGHI on other (A and D on top)
	* Merge two sets of groups to current, resulting in [BEH][CDI]A and FG
	* Move one group to current, resulting in F[BEH][CDI]A and G
	* Merge a set of groups to other, resulting in [BEH][CDI] and [AFG]
	* Recurse with current and other stack swapped
*/

static bool	cmp(int dir, int a, int b)
{
	if (dir < 0)
		return (a < b);
	return (a > b);
}

static void	merge_one_run(t_circular *target, t_circular *other, int run)
{
	int	dir;
	int	n_tb;
	int	n_ot;
	int	n_ob;

	printf("merge run %d\n", run);
	dir = 1;
	if (run < 0)
		dir = -1;
	run *= dir;
	n_tb = (run + 2) / 3;
	n_ot = (run + 1) / 3;
	n_ob = run / 3;
	while (n_tb || n_ot || n_ob)
	{
		if (n_tb
			&& (!n_ot || cmp(dir, circ_peek_bottom(target), circ_peek_top(other)))
			&& (!n_ob || cmp(dir, circ_peek_bottom(target), circ_peek_bottom(other))))
		{
			circ_push(target, circ_shift(target));
			n_tb--;
		}
		else if (n_ot && (!n_ob || cmp(dir, circ_peek_top(other), circ_peek_bottom(other))))
		{
			circ_push(target, circ_pop(other));
			n_ot--;
		}
		else
		{
			circ_push(target, circ_shift(other));
			n_ob--;
		}
	}
}

static void	merge_level(t_circular *c_stack, t_circular *o_stack, t_circular *c_segs, t_circular *o_segs)
{
	size_t	group_size;
	size_t	i;
	int		j;

	group_size = c_segs->count / 3;
	i = 2 * group_size;
	while (i--)
	{
		circ_push(c_segs, circ_shift(c_segs) - circ_pop(o_segs) + circ_shift(o_segs));
		merge_one_run(c_stack, o_stack, circ_peek_top(c_segs));
	}
	i = group_size;
	//printstacks_flipped(c_segs, o_segs, "runs after merge current");
	//printstacks_flipped(c_stack, o_stack, "data after merge current");
	while (i--)
	{
		circ_push(c_segs, -circ_pop(o_segs));
		j = circ_peek_top(c_segs);
		if (j < 0)
			j *= -1;
		while (j--)
			circ_push(c_stack, circ_pop(o_stack));
	}
	//printstacks_flipped(c_segs, o_segs, "runs after move");
	//printstacks_flipped(c_stack, o_stack, "data after move");
	i = group_size;
	while (i--)
	{
		circ_push(o_segs, circ_shift(o_segs) - circ_pop(c_segs) + circ_shift(c_segs));
		merge_one_run(o_stack, c_stack, circ_peek_top(o_segs));
	}
	//printstacks_flipped(c_segs, o_segs, "runs after merge other");
	//printstacks_flipped(c_stack, o_stack, "data after merge other");
	//printstacks_flipped(c_segs, o_segs, "runs after merge other");
	//printstacks_flipped(c_stack, o_stack, "data after merge other");
}

/*
	For split, we do this in reverse:
	* Segment groups are A on current stack, BC on other
	* Split initial group in current stack, resulting in a and aBCa
	* Move one split group to current, resulting in aa and BCa
	* Split initial two groups in other stack, resulting in cbaabc and abc
	* Recurse with current and other swapped
*/

static void	split_one_run(t_circular *from, t_circular *other)
{
	int		run;
	int		dir;

	run = circ_pop(from);
	dir = 1;
	if (run < 0)
		dir = -1;
	circ_unshift(from, (run + dir * 2) / 3);
	circ_push(other, -(run + dir) / 3);
	circ_unshift(other, (run) / 3);
}

static void	split_level(t_circular *current, t_circular *other)
{
	size_t	group_size;
	size_t	i;

	group_size = current->count;
	i = group_size;
	while (i--)
		split_one_run(current, other);
	//printstacks_flipped(current, other, "split current");
	i = group_size;
	while (i--)
		circ_push(current, -circ_pop(other));
	//printstacks_flipped(current, other, "move");
	i = group_size * 2;
	while (i--)
		split_one_run(other, current);
	//printstacks_flipped(current, other, "split other");
}

/*
	At max_len <= 3 the next split would produce 1-length runs for which
	direction doesn't matter and no merging needs to be done.
*/
static void	segment_rec(t_circular *c_stack, t_circular *o_stack, t_circular *c_segs, t_circular *o_segs, int max_len)
{
	split_level(c_segs, o_segs);
	g_flip = !g_flip;
	if (max_len > 3)
		segment_rec(o_stack, c_stack, o_segs, c_segs, (max_len + 2) / 3);
	else
		merge_level(o_stack, c_stack, o_segs, c_segs);
	g_flip = !g_flip;
	printstacks_flipped(c_segs, o_segs, "runs before");
	printstacks_flipped(c_stack, o_stack, "data before");
	merge_level(c_stack, o_stack, c_segs, o_segs);
	printstacks_flipped(c_segs, o_segs, "runs after merge");
	printstacks_flipped(c_stack, o_stack, "data after merge");
}

#include <stdlib.h>

#define N 50

int	main(void)
{
	t_stacks	s;
	t_circular	a;
	t_circular	b;
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
	segment(&s, &a, &b, N);
	printstacks(&s.a, &s.b, "data after");
}
