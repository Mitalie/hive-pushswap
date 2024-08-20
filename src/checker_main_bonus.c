/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:02:53 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/20 15:39:40 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
#include "stacks.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int			num_inputs;
	t_ps_status	status;
	t_stacks	data;

	num_inputs = argc - 1;
	status = input_to_stacks(&data, num_inputs, argv + 1);
	if (status == PS_SUCCESS)
	{
		// TODO: read stdin and apply operations
		// TODO: check whether stacks are properly sorted
	}
	free(data.a);
	free(data.b);
	if (status != PS_SUCCESS)
		write(STDERR_FILENO, "Error\n", 6);
	return (status);
}
