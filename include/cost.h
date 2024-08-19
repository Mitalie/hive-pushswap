/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:59:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 16:46:07 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COST_H
# define COST_H

# include "status.h"

typedef struct s_run_cost
{
	int	*run;
	int	cost;
}	t_run_cost;

t_ps_status	select_cheapest(t_runs *runs, int num_items);

#endif
