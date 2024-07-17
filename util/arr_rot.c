/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:05:35 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 13:29:02 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arr_rot.h"

/*
	forward moves first to last, reverse moves last to first
*/
void	byte_arr_rot(unsigned char *arr, int size, bool reverse)
{
	unsigned char	tmp;
	int				i;

	if (size < 2)
		return ;
	if (!reverse)
	{
		i = 0;
		tmp = arr[i];
		while (i++ < size - 1)
			arr[i - 1] = arr[i];
		arr[i - 1] = tmp;
	}
	else
	{
		i = size;
		tmp = arr[i - 1];
		while (--i)
			arr[i] = arr[i - 1];
		arr[i] = tmp;
	}
}
