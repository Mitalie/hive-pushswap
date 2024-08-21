/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:46:59 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/21 12:47:45 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRC_H
# define CIRC_H

# include <stddef.h>

/*
	Circular array, supporting random access and push/pop at both ends.
*/
typedef struct s_circ	t_circ;

t_circ	*circ_alloc(size_t size);
size_t	circ_len(t_circ *c);
int		*circ_ptr(t_circ *c, size_t idx);
void	circ_push_back(t_circ *c, int v);
void	circ_push_front(t_circ *c, int v);
int		circ_pop_back(t_circ *c);
int		circ_pop_front(t_circ *c);
int		circ_peek_back(t_circ *c);
int		circ_peek_front(t_circ *c);

#endif
