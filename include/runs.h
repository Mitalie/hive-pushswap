/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:47:35 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/12 17:22:21 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNS_H
# define RUNS_H

# include "circ.h"
# include <stdbool.h>
# include <stddef.h>

typedef enum e_loc
{
	A1,
	A2,
	B1,
	B2,
	NUM_LOCS,
}	t_loc;

typedef struct s_runs
{
	t_loc	current_loc;
	int		num_runs[NUM_LOCS];
	int		total_runs;
	t_circ	*a;
	t_circ	*b;
}	t_runs;

bool	init_runs(t_runs *runs, int num_items);

#endif
