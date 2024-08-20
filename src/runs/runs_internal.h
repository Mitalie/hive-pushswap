/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:59:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/20 15:23:09 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNS_INTERNAL_H
# define RUNS_INTERNAL_H

# include "status.h"
# include "runs.h"

typedef struct s_run_cost
{
	int	*run;
	int	cost;
}	t_run_cost;

t_ps_status	runs_select_cheapest(t_runs *runs, int num_items);

#endif
