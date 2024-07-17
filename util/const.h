/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:00:49 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 18:08:01 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# ifndef N
#  define N 9
# endif

# if N > 9
#  error N > 9 not supported
# endif

extern const int	g_t[10];
extern const int	g_te[10];
extern const int	g_fact[10];

#endif
