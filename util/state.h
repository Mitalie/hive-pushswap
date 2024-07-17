/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:38:47 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 18:05:07 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include <stdbool.h>

# include "const.h"

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

bool	sop_r(t_state *s, bool a, bool b);
bool	sop_rr(t_state *s, bool a, bool b);
bool	sop_s(t_state *s, bool a, bool b);
bool	sop_p(t_state *s, bool a, bool b);

typedef enum e_sop
{
	SOP_SS,
	SOP_SA,
	SOP_SB,
	SOP_RR,
	SOP_RA,
	SOP_RB,
	SOP_RRR,
	SOP_RRA,
	SOP_RRB,
	SOP_PA,
	SOP_PB,
	NUM_SOP,
}	t_sop;

bool	sop(t_state *s, t_sop op);

#endif
