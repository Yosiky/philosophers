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
	static char				flag = 0;

	if (!flag)
	{
		gettimeofday(&t, NULL);
		flag = 1;
	}
	return (&t);
}

void	philo_say(int i, const char *str)
{
	static struct timeval	t;
	static struct timeval	*start;
	static char				flag = 0;

	if (!flag)
	{
		start = get_time_start_work();
		++flag;
	}
	pthread_mutex_lock(get_mutex_print());
	gettimeofday(&t, NULL);
	ee_putnbr(1, (t.tv_sec - start->tv_sec) * 1000 + t.tv_usec - start->tv_usec);
	write(1, " ", 1);
	ee_putnbr(1, i);
	write(1, " ", 1);
	ee_putstr(1, str);
	pthread_mutex_unlock(get_mutex_print());
}
