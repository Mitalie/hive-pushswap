/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:13:36 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/17 16:09:42 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "util/state.h"

int	main(void)
{
	t_state	s;

	s = decode(0);
	printstate(&s);
	sop_p(&s, false, true);
	sop_p(&s, false, true);
	printstate(&s);
	sop_r(&s, true, true);
	sop_r(&s, true, true);
	printstate(&s);
	// for (int i = 0; i <= 120; i++)
	// {
	// 	s = decode(i);
	// 	printstate(&s);
	// }
	// s = decode(362879);
	// printstate(&s);
	// s = decode(68 * 362880);
	// printstate(&s);
	// sop_s(&s, true, false);
	// printstate(&s);
	// sop_s(&s, false, true);
	// printstate(&s);
	// sop_p(&s, false, true);
	// sop_p(&s, false, true);
	// printstate(&s);
	// sop_rr(&s, true, true);
	// printstate(&s);
	// sop_r(&s, true, true);
	// printstate(&s);
}
