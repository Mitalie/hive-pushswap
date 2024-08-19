/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:17:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/19 16:45:57 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

typedef enum e_ps_status
{
	PS_SUCCESS = 0,
	PS_ERR_ALLOC_FAILURE,
	PS_ERR_INVALID_INPUT,
	PS_ERR_DUPLICATE_INPUT,
}	t_ps_status;

#endif
