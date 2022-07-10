/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:52:56 by eestelle          #+#    #+#             */
/*   Updated: 2022/07/03 20:25:32 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_symbol(const char c)
{
	return (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ');
}

int32_t	ee_atoi(const char *str, int64_t *ptr)
{
	int	i;
	int	sign;

	if (str == NULL)
		return (1);
	i = 0;
	sign = 1;
	*ptr = 0;
	while (check_symbol(str[i]))
		++i;
	if (str[i] == '-')
	{
		++i;
		sign = -1;
	}
	while ('0' <= str[i] && str[i] <= '9' && (int32_t)(*ptr) >= 0)
	{
		if ((int32_t)(*ptr) > (int32_t)(*ptr) * 10 + str[i] - '0')
			break ;
		*ptr = *ptr * 10 + str[i++] - '0';
	}
	*ptr = (int64_t)sign * (*ptr) * (str[i] == '\0');
	if (*ptr)
		return (0);
	return (2);
}
