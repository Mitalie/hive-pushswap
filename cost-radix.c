/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost-radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:44:53 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/19 19:09:42 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum e_loc {
	TOP_A,
	TOP_B,
	BOT_A,
	BOT_B,
	NUM_LOC,
}	t_loc;

static const char	*g_loc_name[NUM_LOC] = {
	"At", "Bt", "Ab", "Bb",
};

typedef struct s_cost {
	int	ops;
	int	ops_2way;
	int	split_2way_a;
	int	split_ab;
}	t_cost;

typedef struct s_costs {
	t_cost	costs[NUM_LOC];
}	t_costs;

#define NUM_FIXED 8

static const int	g_fixed_costs[NUM_FIXED * NUM_LOC] = {
	0, 0, 0, 0,
	0, 1, 1, 2,
	1, 3, 3, 4,
	5, 6, 6, 7,
	9, 8, 9, 9,
//	data-independent sorts
	13, 11, 14, 13,
	16, 14, 17, 17,
	20, 19, 24, 21,
//	optimal sorts
//	12, 10, 13, 13,
//	15, 13, 16, 16,
//	18, 16, 20, 19,
//	21, 19, 24, 23,
//	24, 21, 27, 26,
};

static const int	g_split_cost[NUM_LOC][NUM_LOC] = {
{0, 1, 1, 2},
{1, 0, 2, 1},
{1, 2, 0, 3},
{2, 1, 3, 0},
};

static t_loc	next_loc(t_loc curr, int offset)
{
	return ((curr + offset) % NUM_LOC);
}

static void	calc_sort2(t_costs *arr, int ab, t_loc curr)
{
	int		ops;
	int		a;
	int		b;
	t_cost	*curr_entry;

	b = 0;
	curr_entry = &arr[ab].costs[curr];
	while (b <= ab)
	{
		a = ab - b;
		ops = a * g_split_cost[curr][next_loc(curr, 1)]
			+ arr[a].costs[next_loc(curr, 1)].ops
			+ b * g_split_cost[curr][next_loc(curr, 2)]
			+ arr[b].costs[next_loc(curr, 2)].ops;
		if (ops < curr_entry->ops_2way)
		{
			curr_entry->ops_2way = ops;
			curr_entry->split_2way_a = a;
		}
		b++;
	}
}

static void	calc_sort3(t_costs *arr, int abc, t_loc curr)
{
	int		ops;
	int		ab;
	int		c;
	t_cost	*curr_entry;

	c = 0;
	curr_entry = &arr[abc].costs[curr];
	while (c <= abc)
	{
		ab = abc - c;
		ops = arr[ab].costs[curr].ops_2way
			+ c * g_split_cost[curr][next_loc(curr, 3)]
			+ arr[c].costs[next_loc(curr, 3)].ops;
		if (ops < curr_entry->ops)
		{
			curr_entry->ops = ops;
			curr_entry->split_ab = ab;
		}
		c++;
	}
}

static void	calc(t_costs *arr, int max_n)
{
	int	n;
	int	loc;

	n = NUM_FIXED;
	while (n < max_n)
	{
		loc = 0;
		while (loc < NUM_LOC)
		{
			arr[n].costs[loc].ops = INT_MAX / 3;
			arr[n].costs[loc].ops_2way = INT_MAX / 3;
			loc++;
		}
		loc = 0;
		while (loc < NUM_LOC)
		{
			calc_sort2(arr, n, loc);
			calc_sort3(arr, n, loc);
			loc++;
		}
		n++;
	}
}

static void	print_entry(t_costs *arr, int n, t_loc curr)
{
	t_cost	*curr_entry;
	t_cost	*sort2_entry;
	int		ab;
	int		a;

	curr_entry = &arr[n].costs[curr];
	if (n < NUM_FIXED)
	{
		printf("  from %s: %d\n", g_loc_name[curr], curr_entry->ops);
		return ;
	}
	ab = curr_entry->split_ab;
	sort2_entry = &arr[curr_entry->split_ab].costs[curr];
	a = sort2_entry->split_2way_a;
	printf("  from %s: %d %s=%d %s=%d %s=%d\n",
		g_loc_name[curr], curr_entry->ops,
		g_loc_name[next_loc(curr, 1)], a,
		g_loc_name[next_loc(curr, 2)], ab - a,
		g_loc_name[next_loc(curr, 3)], n - ab);
	/*a = curr_entry->split_2way_a;
	printf("  from %s: %d %s=%d %s=%d (2way)\n",
		g_loc_name[curr], curr_entry->ops_2way,
		g_loc_name[next_loc(curr, 1)], a,
		g_loc_name[next_loc(curr, 2)], n - a);*/
}

int	main(int argc, char **argv)
{
	t_costs	*arr;
	int		i;
	int		n;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]) + 1;
	arr = malloc(sizeof(*arr) * n);
	if (!arr)
		return (2);
	i = 0;
	while (i < NUM_FIXED * NUM_LOC && i < n * NUM_LOC)
	{
		arr[i / NUM_LOC].costs[i % NUM_LOC].ops = g_fixed_costs[i];
		arr[i / NUM_LOC].costs[i % NUM_LOC].ops_2way = g_fixed_costs[i];
		i++;
	}
	calc(arr, n);
	i = 0;
	while (i < n * NUM_LOC)
	{
		if (i % NUM_LOC == 0)
			printf("sort %d\n", i / NUM_LOC);
		print_entry(arr, i / NUM_LOC, i % NUM_LOC);
		i++;
	}
	free(arr);
}
