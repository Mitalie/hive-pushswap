/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:31:31 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 15:15:19 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_INTERNAL_H
# define MERGE_INTERNAL_H

# include "circ.h"

typedef enum e_merge_source
{
	CURR_BOT,
	OTHER_TOP,
	OTHER_BOT,
	NUM_SOURCES
}	t_merge_source;

typedef struct s_merge_state
{
	t_circ				*runs_curr;
	t_circ				*runs_other;
	t_circ				*data_curr;
	t_circ				*data_other;
	const char *const	*pushswap_ops;
	int					run_items[NUM_SOURCES];
	int					total_run_items;
	int					run_dir;
}	t_merge_state;

void	merge_run(t_merge_state *s);

#endif
