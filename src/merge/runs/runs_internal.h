/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:59:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/20 16:18:30 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNS_INTERNAL_H
# define RUNS_INTERNAL_H

# include "../merge_internal.h"
# include "status.h"

typedef struct s_run_cost
{
	int	*run;
	int	cost;
}	t_run_cost;

typedef struct t_pass_cb	t_pass_cb;

typedef						t_ps_status (t_pass_cb_func)(
	t_runs *runs, size_t pass, t_pass_cb *data);

typedef struct t_pass_cb
{
	t_pass_cb_func	*func;
	int				num_items;
	size_t			best_pass;
	size_t			best_cost;
}	t_pass_cb;

t_ps_status	merge_runs_get_cost(t_runs *runs, int num_items, size_t *cost);
t_ps_status	merge_runs_select_cheapest(t_runs *runs, int num_items);
t_ps_status	merge_runs_populate(
				t_runs *runs, size_t passes, t_pass_cb *callback);

#endif
