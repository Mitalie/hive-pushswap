/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost-radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:44:53 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/15 15:46:24 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

/* records costs for one size from each position */
typedef struct s_costs {
	size_t	tl;
	size_t	tr;
	size_t	bl;
	size_t	br;
}	t_costs;

int	main(int argc, char **argv)
{
	t_costs	*arr;

	if (argc != 2)
		return (1);
	arr = malloc(sizeof(*arr) * atoi(argv[1]));
	if (!arr)
		return (2);
	free(arr);
}
