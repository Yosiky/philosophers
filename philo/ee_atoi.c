/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:52:56 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 18:01:13 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_symbol(const char c)
{
	return (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ');
}

int	ee_atoi(const char *str, int *ptr)
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
	while ('0' <= str[i] && str[i] <= '9')
		*ptr = *ptr * 10 + str[i++] - '0';
	*ptr = sign * (*ptr);
	if (str[i] != '\0')
	{
		*ptr = 0;
		return (2);
	}
	return (0);
}
