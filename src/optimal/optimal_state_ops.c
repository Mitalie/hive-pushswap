/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_state_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:11:03 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/30 18:05:07 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimal_internal.h"

int	optimal_state_op(int state_num, t_ps_op op)
{
	t_optimal_state	state;

	optimal_state_dec(&state, state_num);
	// TODO
	return (optimal_state_enc(&state));
}
