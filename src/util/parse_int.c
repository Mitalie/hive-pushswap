/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:18:55 by amakinen          #+#    #+#             */
/*   Updated: 2024/08/12 14:17:26 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include <limits.h>

static bool	isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static bool	isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
	Parse decimal integer from a string, ensuring it doesn't contain additional
	garbage. If value_out is not NULL, the parsed value is stored there.
*/
bool	parse_int(const char *str, int *value_out)
{
	int	sign;
	int	digit;
	int	value;

	while (isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	value = 0;
	while (isdigit(*str))
	{
		digit = *str++ - '0';
		if ((sign > 0 && value > (INT_MAX - digit) / 10)
			|| (sign < 0 && value < (INT_MIN + digit) / 10))
			return (false);
		value = value * 10 + sign * digit;
	}
	while (isspace(*str))
		str++;
	if (*str == 0 && value_out)
		*value_out = value;
	return (*str == 0);
}
