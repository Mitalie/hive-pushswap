/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:06:58 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/04 13:29:26 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
#include "stacks.h"
#include "optimal.h"
#include "runs.h"
#include "merge.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int			num_inputs;
	t_ps_status	status;
	t_stacks	data;
	t_runs		runs;

	num_inputs = argc - 1;
	runs.a = 0;
	runs.b = 0;
	status = input_to_stacks(&data, num_inputs, argv + 1);
	if (num_inputs >= 2 && num_inputs <= 12 && status == PS_SUCCESS)
		status = optimal_sort(&data, num_inputs);
	else if (status == PS_SUCCESS)
	{
		status = calculate_runs(&runs, num_inputs);
		if (status == PS_SUCCESS)
			pushswap_merge(&data, &runs);
	}
	free(data.a);
	free(data.b);
	free(runs.a);
	free(runs.b);
	if (status != PS_SUCCESS)
		write(STDERR_FILENO, "Error\n", 6);
	return (status);
}
