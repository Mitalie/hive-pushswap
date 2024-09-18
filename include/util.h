/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:16:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/18 14:43:05 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdbool.h>

/*
	Parse decimal integer from a string, ensuring it doesn't overflow or contain
	additional garbage besides leading or trailing whitespace. Leading plus sign
	is allowed. If value_out is not NULL, the parsed value is stored there.
*/
bool	parse_int(const char *str, int *value_out);

/*
	Rotate an array of ints by one. Forward direction moves first element to
	last, reverse direction moves last element to first.
*/
void	int_arr_rot_one(int *arr, int size, bool reverse);

int		factorial(int n);

#endif
