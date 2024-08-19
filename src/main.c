/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:06:58 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 16:46:53 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
#include "stacks.h"
#include "runs.h"
#include "cost.h"
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
	if (status == PS_SUCCESS)
		status = init_runs(&runs, num_inputs);
	if (status == PS_SUCCESS)
		status = select_cheapest(&runs, num_inputs);
	if (status == PS_SUCCESS)
		pushswap_merge(&data, &runs);
	free(data.a);
	free(data.b);
	free(runs.a);
	free(runs.b);
	if (status != PS_SUCCESS)
		write(STDERR_FILENO, "Error\n", 6);
	return (status);
}
