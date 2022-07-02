/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   say_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:31:05 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 20:34:33 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval	*get_time_start_work(void)
{
	static struct timeval	t;

	return (&t);
}

void	philo_say(int i, const char *str)
{
	static struct timeval	t;

	pthread_mutex_lock(get_mutex_print());
	gettimeofday(&t, NULL);
	ee_putnbr(1, ((t.tv_sec - get_time_start_work()->tv_sec) * 1000 + t.tv_usec - get_time_start_work()->tv_usec) / 1000);
	write(1, " ", 1);
	ee_putnbr(1, i);
	write(1, " ", 1);
	ee_putstr(1, str);
	pthread_mutex_unlock(get_mutex_print());
}
