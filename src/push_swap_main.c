/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:06:58 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/20 15:14:42 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "merge.h"
#include "optimal.h"
#include "stacks.h"
#include "status.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	int			num_inputs;
	t_ps_status	status;
	t_stacks	data;

	num_inputs = argc - 1;
	if (num_inputs == 0)
		return (PS_SUCCESS);
	status = stacks_from_input(&data, num_inputs, argv + 1);
	if (status == PS_SUCCESS)
	{
		if (num_inputs > OPT_MAX_ITEMS)
			status = pushswap_merge(&data, num_inputs, STDOUT_FILENO);
		else if (num_inputs > 1)
			status = pushswap_optimal(&data, num_inputs, STDOUT_FILENO);
	}
	stacks_release(&data);
	if (status != PS_SUCCESS)
		write(STDERR_FILENO, "Error\n", 6);
	return (status);
}
