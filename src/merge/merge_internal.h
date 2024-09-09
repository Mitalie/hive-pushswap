/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:31:31 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/09 17:54:37 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_INTERNAL_H
# define MERGE_INTERNAL_H

# include "circ.h"
# include "ops.h"

typedef enum e_merge_source
{
	CURR_BOT,
	OTHER_TOP,
	OTHER_BOT,
	NUM_SOURCES
}	t_merge_source;

typedef struct s_merge_state
{
	t_circ					*runs_curr;
	t_circ					*runs_other;
	t_circ					*data_curr;
	t_circ					*data_other;
	const t_ps_op *const	*pushswap_ops;
	int						run_items[NUM_SOURCES];
	int						total_run_items;
	int						run_dir;
	size_t					output_queue_size;
	t_circ					*output_queue;
	int						output_fd;
	t_stacks				*stacks;
}	t_merge_state;

void	merge_run(t_merge_state *s);

void	merge_op_queue_add(t_merge_state *s, t_ps_op op);
void	merge_op_queue_flush(t_merge_state *s);

#endif
