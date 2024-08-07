/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:44:10 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/07 18:54:03 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRC_INTERNAL_H
# define CIRC_INTERNAL_H

# include "circ.h"

/*
	start points at the first slot, which is non-empty unless count == 0
	end points at one past the last slot, which is empty unless count == size
*/
struct	s_circ
{
	size_t	start;
	size_t	end;
	size_t	count;
	size_t	size;
	int		arr[];
};

#endif
