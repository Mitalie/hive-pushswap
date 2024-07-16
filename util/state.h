/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:38:47 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/16 15:29:06 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include <stdbool.h>

# ifndef N
#  define N 9
# endif

typedef struct s_state
{
	unsigned char	a;
	unsigned char	b;
	unsigned char	c;
	unsigned char	num[N];
}	t_state;

int		encode(t_state *s);
t_state	decode(int v);
void	printstate(t_state *s);

void	sop_r(t_state *s, bool a, bool b);
void	sop_rr(t_state *s, bool a, bool b);
void	sop_s(t_state *s, bool a, bool b);
void	sop_p(t_state *s, bool a, bool b);

#endif
