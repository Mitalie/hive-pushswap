/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:06:58 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 16:13:57 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stacks.h"
#include "runs.h"
#include "cost.h"
#include "merge.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int			num_inputs;
	t_stacks	data;
	t_runs		runs;

	num_inputs = argc - 1;
	if (!input_to_stacks(&data, num_inputs, argv + 1))
		return (1);
	if (!init_runs(&runs, num_inputs))
		return (2);
	if (!select_cheapest(&runs, num_inputs))
		return (3);
	pushswap_merge(&data, &runs);
	free(data.a);
	free(data.b);
	free(runs.a);
	free(runs.b);
}
