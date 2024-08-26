/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:02:53 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/26 13:54:28 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
#include "stacks.h"
#include "ops.h"
#include "read_ops.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static t_ps_status	perform_ops_from_stdin(t_stacks *data)
{
	t_read_ops_state	s;
	t_ps_status			status;
	t_ps_op				op;
	bool				end;

	read_ops_init(&s, STDIN_FILENO);
	while (true)
	{
		status = read_ops_next(&s, &end, &op);
		if (status != PS_SUCCESS)
			return (status);
		if (end)
			return (PS_SUCCESS);
		perform_op(data, op);
	}
}

int	main(int argc, char **argv)
{
	int			num_inputs;
	t_ps_status	status;
	t_stacks	data;

	num_inputs = argc - 1;
	status = input_to_stacks(&data, num_inputs, argv + 1);
	if (status == PS_SUCCESS)
		status = perform_ops_from_stdin(&data);
	if (status == PS_SUCCESS)
	{
		// TODO: check whether stacks are properly sorted
	}
	free(data.a);
	free(data.b);
	if (status != PS_SUCCESS)
		write(STDERR_FILENO, "Error\n", 6);
	return (status);
}
