/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:44:32 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 18:02:14 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int32_t	ee_putnbr(int fd, const int32_t n)
{
	static char			arr[10];
	static int32_t		len;
	static long long	value;

	value = n;
	if (value < 0)
	{
		write(fd, "-", 1);
		value *= -1;
	}
	else if (value == 0)
		return ((int32_t)write(fd, "0", 1));
	len = 0;
	while (value)
	{
		arr[10 - 1 - (len++)] = '0' + value % 10;
		value /= 10;
	}
	write(fd, arr + 10 - len, (size_t)len);
	return (len);
}
