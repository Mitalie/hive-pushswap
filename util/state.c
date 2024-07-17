/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:40:13 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 18:02:12 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <stdio.h>
#include "arr_rot.h"
#include "const.h"

int	encode(t_state *s)
{
	int	stack;
	int	perm;
	int	i;
	int	digit;
	int	tmp;

	i = N - 1;
	perm = 0;
	while (i--)
	{
		digit = 0;
		tmp = s->num[i];
		while (digit < N - i - 1 && tmp > s->num[i + digit + 1])
		{
			s->num[i + digit] = s->num[i + digit + 1];
			digit++;
		}
		s->num[i + digit] = tmp;
		perm += digit * g_fact[N - i - 1];
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
