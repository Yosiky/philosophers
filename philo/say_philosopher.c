/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   say_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:31:05 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 17:40:32 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_say(int i, const char *str)
{
	static struct timeval	t;

	pthread_mutex_lock(get_mutex_print());
	gettimeofday(&t, NULL);
	ee_putnbr(1, t.tv_sec);
	write(1, " ", 1);
	ee_putnbr(1, i);
	write(1, " ", 1);
	ee_putstr(1, str);
	pthread_mutex_unlock(get_mutex_print());
}
