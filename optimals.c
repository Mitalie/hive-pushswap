/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:13:36 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/15 17:25:18 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#define N 9

typedef struct s_state {
	char	a;
	char	b;
	char	c;
	char	num[N];
}	t_state;

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
	}
	stack = g_te[s->a] + g_t[s->b] + s->c;
	return (stack * g_fact[N] + perm);
}

t_state	decode(int v)
{
	t_state	s;
	int		perm;
	int		stack;
	int		i;
	int		nums[N];

	s = (t_state){0};
	stack = v / g_fact[N];
	perm = v % g_fact[N];
	while (s.a < N && stack > g_te[s.a + 1])
		s.a++;
	while (s.b < s.a && (stack - g_t[s.a]) > g_t[s.b + 1])
		s.b++;
	s.c = stack - g_te[s.a] - g_t[s.b];
	i = 0;
	while (i < N)
		nums[i] = i + 1;
	while (i--)
	{
		v = perm / g_fact[i];
		perm = perm % g_fact[i];
		s.num[N - i - 1] = nums[v];
		while (++v < N)
			nums[v - 1] = nums[v];
	}
}
