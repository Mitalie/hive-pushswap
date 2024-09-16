/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:31:31 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/16 16:45:21 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_INTERNAL_H
# define MERGE_INTERNAL_H

# include "circ.h"
# include "ops.h"
# include "status.h"

typedef enum e_merge_source
{
	CURR_BOT,
	OTHER_TOP,
	OTHER_BOT,
	NUM_SOURCES
}	t_merge_source;

/*
	Variables that live for the entire merge sort process and are needed in the
	inner functions.
*/
typedef struct s_merge_state
{
	size_t		output_queue_size;
	t_circ		*output_queue;
	int			output_fd;
	t_stacks	*stacks;
}	t_merge_state;

/*
	Variables that reset for each pass during the merge.

	These essentially cache the choice of current destination stack (A or B) to
	eliminate repeated checks and code duplication in inner functions.
*/
typedef struct s_merge_pass_state
{
	t_circ					*runs_curr;
	t_circ					*runs_other;
	t_circ					*data_curr;
	t_circ					*data_other;
	const t_ps_op *const	*pushswap_ops;
}	t_merge_pass_state;

/*
	Variables that reset for each run during a pass and are needed in the inner
	functions.
*/
typedef struct s_merge_run_state
{
	int	run_items[NUM_SOURCES];
	int	run_dir;
}	t_merge_run_state;

t_ps_status	merge_run(t_merge_state *merge, t_merge_pass_state *pass);

t_ps_status	merge_op_queue_add(t_merge_state *merge, t_ps_op op);
t_ps_status	merge_op_queue_flush(t_merge_state *merge);

#endif
