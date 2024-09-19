/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:02:53 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/19 17:18:12 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"
#include "stacks.h"
#include "ops.h"
#include <stdbool.h>
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

/*
	Valid result has empty stack B and sorted stack A, i.e. every item on A is
	smaller than the one below it (or equal, but rules exclude duplicates).
*/
static bool	check_stacks_sorted(t_stacks *data)
{
	size_t	i;

	if (circ_len(data->b) > 0)
		return (false);
	i = circ_len(data->a);
	while (i-- > 1)
		if (*circ_ptr(data->a, i) > *circ_ptr(data->a, i - 1))
			return (false);
	return (true);
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
		if (check_stacks_sorted(&data))
			write(STDOUT_FILENO, "OK\n", 3);
		else
			write(STDOUT_FILENO, "KO\n", 3);
	}
	release_stacks(&data);
	if (status != PS_SUCCESS)
		write(STDERR_FILENO, "Error\n", 6);
	return (status);
}
