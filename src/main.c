/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:06:58 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/12 17:42:26 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runs.h"
#include "cost.h"
#include <stdio.h>
#include <stdlib.h>

static void	printruns(t_runs *runs)
{
	int	i;

	printf("A :");
	i = 0;
	while (i < runs->num_runs[A1] + runs->num_runs[A2])
		printf(" %d", circ_get(runs->a, i++));
	printf("\nB :");
	i = 0;
	while (i < runs->num_runs[B1] + runs->num_runs[B2])
		printf(" %d", circ_get(runs->b, i++));
	printf("\n");
}

int	main(int argc, char **argv)
{
	int		num_inputs;
	t_runs	runs;

	(void)argv;
	num_inputs = argc - 1;
	if (!init_runs(&runs, num_inputs))
		return (1);
	printruns(&runs);
	if (!select_cheapest(&runs, num_inputs))
		return (2);
	printruns(&runs);
	free(runs.a);
	free(runs.b);
}
