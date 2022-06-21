/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   say_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:31:05 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/27 15:06:08 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_say(int i, const char *str)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	ee_putnbr(1, t.tv_sec);
	write(1, " ", 1);
	ee_putnbr(1, i);
	write(1, " ", 1);
	ee_putstr(1, str);
}
