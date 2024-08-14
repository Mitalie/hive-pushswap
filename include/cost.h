/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:59:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/14 12:42:44 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COST_H
# define COST_H

typedef struct s_run_cost
{
	int	*run;
	int	cost;
}	t_run_cost;

bool	select_cheapest(t_runs *runs, int num_items);

#endif
