/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_state_enc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:03:12 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 17:35:31 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal_internal.h"
#include "util.h"

/*
	First separate num_b and permutation number with division and remainder,
	then decode the permutation number as Lehmer code and create the permuted
	array.

	Lehmer code is stored as an integer using factorial number system. For each
	position in the permutation, extract the most significant Lehmer code digit
	`d` that hasn't been used yet, and select the `d`th smallest item that
	hasn't been selected yet. A simple sub-array rotation keeps unused items
	sorted on the right side of the array while appending the selected item to
	the permutation on the left side.
*/
void	optimal_state_dec(t_opt_state_arr *s, int state_num, int num_items)
{
	int	i;
	int	lehmer_digit;
	int	*next_item;

	s->num_b = state_num % (num_items + 1);
	s->num_a = num_items - s->num_b;
	state_num = state_num / (num_items + 1);
	i = 0;
	while (i++ < num_items)
		s->items[i - 1] = i;
	next_item = s->items;
	i = num_items;
	while (--i)
	{
		lehmer_digit = state_num / util_factorial(i);
		state_num = state_num % util_factorial(i);
		util_int_arr_rot_one(next_item++, lehmer_digit + 1, true);
	}
}

/*
	Reverse of the Lehmer code decoding process: start from the right side of
	the permutation and return each item to the sorted set of unused items,
	counting how many items were skipped to select it, and adding the resulting
	count as a digit to the factorial number.

	Finally combine the resulting permutation number with num_b to arrive at the
	state number.
*/
int	optimal_state_enc(t_opt_state_arr *s, int num_items)
{
	unsigned char	item;
	int				i;
	int				lehmer_digit;
	int				lehmer_fact;

	i = num_items - 1;
	lehmer_fact = 0;
	while (i--)
	{
		lehmer_digit = 0;
		item = s->items[i];
		while (i + lehmer_digit + 1 < num_items
			&& item > s->items[i + lehmer_digit + 1])
		{
			s->items[i + lehmer_digit] = s->items[i + lehmer_digit + 1];
			lehmer_digit++;
		}
		s->items[i + lehmer_digit] = item;
		lehmer_fact += lehmer_digit * util_factorial(num_items - i - 1);
	}
	return (lehmer_fact * (num_items + 1) + s->num_b);
}
