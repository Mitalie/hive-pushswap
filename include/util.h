/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:16:38 by amakinen          #+#    #+#             */
/*   Updated: 2024/09/04 15:55:11 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdbool.h>

bool	parse_int(const char *s, int *v);
void	int_arr_rot_one(int *arr, int size, bool reverse);
int		factorial(int n);

#endif
