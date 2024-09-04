/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factorial.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:54:49 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/04 17:41:45 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

/*
int	factorial(int n)
{
	if (n <= 1)
		return (1);
	return (n * factorial(n - 1));
}
*/

/*
	Factorial of 13 is already higher than INT_MAX, so we can implement it
	with a small hard-coded lookup table. This is a lot more efficient than
	multiple rounds of multiplication.
*/

#define FACT_MAX 12

static const int	g_fact[FACT_MAX + 1] = {
	1,
	1,
	2,
	6,
	24,
	120,
	720,
	5040,
	40320,
	362880,
	3628800,
	39916800,
	479001600,
};

int	factorial(int n)
{
	if (n < 0 || n > FACT_MAX)
		return (0);
	return (g_fact[n]);
}
