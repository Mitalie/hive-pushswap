/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:13 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 16:11:52 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <stdio.h>
#include "arr_rot.h"

const int	g_t[10] = {
	0, 1, 3, 6, 10, 15, 21, 28, 36, 45
};

const int	g_te[10] = {
	0, 1, 4, 10, 20, 35, 56, 84, 120, 165
};

const int	g_fact[10] = {
	1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880
};

int	encode(t_state *s)
{
	int	stack;
	int	perm;
	int	i;
	int	v;
	int	nums[9];

	i = 0;
	perm = 0;
	while (i < N)
	{
		v = i;
		nums[i] = s->num[i];
		while (v > 0 && nums[v] < nums[v - 1])
		{
			nums[v] = nums[v - 1];
			v--;
		}
		perm += v * g_fact[i];
		i++;
	}
	stack = g_te[s->a] + g_t[s->b] + s->c;
	return (stack * g_fact[N] + perm);
}

t_state	decode(int v)
{
	t_state	s;
	int		lehmer_digit;
	int		stack;
	int		i;

	s = (t_state){0};
	stack = v / g_fact[N];
	while (s.a < N && stack >= g_te[s.a + 1])
		s.a++;
	while (s.b < s.a && (stack - g_te[s.a]) >= g_t[s.b + 1])
		s.b++;
	s.c = stack - g_te[s.a] - g_t[s.b];
	i = N + 1;
	while (--i)
		s.num[i - 1] = i;
	while (i < N)
	{
		lehmer_digit = v / g_fact[N - i - 1] % (N - i);
		byte_arr_rot(s.num + i++, lehmer_digit + 1, true);
	}
	return (s);
}

void	printstate(t_state *s)
{
	int	i;

	i = 0;
	printf("(t) ");
	while (i < N - s->a)
		printf("%d ", s->num[i++]);
	printf("... ");
	while (i < N - s->b)
		printf("%d ", s->num[i++]);
	printf("(b) | (b) ");
	while (i < N - s->b + s->c)
		printf("%d ", s->num[i++]);
	printf("... ");
	while (i < N)
		printf("%d ", s->num[i++]);
	printf("(t)\n");
}
