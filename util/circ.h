/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circ.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:09:15 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/15 12:23:25 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRC_H
# define CIRC_H

# include <stddef.h>

/*
	circular array
	start points at non-empty slot unless empty
	end points at empty slot unless full
*/
typedef struct s_circular {
	size_t	start;
	size_t	end;
	size_t	count;
	size_t	size;
	int		*arr;
}	t_circular;

void	circ_init(t_circular *c, size_t size);
void	circ_deinit(t_circular *c);
void	circ_push(t_circular *c, int v);
int		circ_pop(t_circular *c);
void	circ_unshift(t_circular *c, int v);
int		circ_shift(t_circular *c);
void	circ_swap_top(t_circular *c);
int		circ_peek_top(t_circular *c);
int		circ_peek_bottom(t_circular *c);
/* pop + unshift */
void	circ_rotate(t_circular *c);
/* shift + push */
void	circ_revrotate(t_circular *c);

#endif
