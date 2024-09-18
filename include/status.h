/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:17:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/18 17:19:45 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

/*
	Error codes that can be returned from various functions when the program
	can't continue normal operation. The push_swap assignment doesn't allow
	custom error messages to distinguish different types of errors, but they
	are reported via the program's exit code.
*/
typedef enum e_ps_status
{
	PS_SUCCESS = 0,
	PS_ERR_ALLOC_FAILURE,
	PS_ERR_WRITE_FAILURE,
	PS_ERR_READ_FAILURE,
	PS_ERR_INPUT_ITEM_INVALID,
	PS_ERR_INPUT_ITEM_DUPLICATE,
	PS_ERR_INPUT_OP_INVALID,
}	t_ps_status;

#endif
