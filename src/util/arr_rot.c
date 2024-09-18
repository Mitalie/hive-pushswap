/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_rot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:37:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/18 14:23:46 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

void	int_arr_rot_one(int *arr, int size, bool reverse)
{
	int	tmp;
	int	i;

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
