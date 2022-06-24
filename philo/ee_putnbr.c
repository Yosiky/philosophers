/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:44:32 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 13:51:44 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ee_putnbr(int fd, const int n)
{
	static char			arr[10];
	static size_t		len;
	static long long	value;

	value = n;
	if (value < 0)
	{
			write(fd, "-", 1);
			value *= -1;
	}
	else if (value == 0)
	{
			return (write(fd, "0", 1));
	}
	len = 0;
	while (value)
	{
			arr[10 - 1 - (len++)] = '0' + value % 10;
			value /= 10;
	}
	write(fd, arr + 10 - len, len);
	return (len);
}

