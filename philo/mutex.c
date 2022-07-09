/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:37:21 by eestelle          #+#    #+#             */
/*   Updated: 2022/07/03 21:08:43 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*get_mutex_struct(void)
{
	static t_mutex	mutex;

	return (&mutex);
}

int	destroy_tmutex(t_mutex *elem, int8_t mask)
{
	if (mask & 1)
	{
		while (elem->size-- > 0)
			pthread_mutex_destroy(&elem->array[elem->size]);
		free(elem->array);
	}
	if (mask & 2)
		pthread_mutex_destroy(&elem->print);
	if (mask & 4)
		pthread_mutex_destroy(&elem->number);
	if (mask & 8)
		pthread_mutex_destroy(&elem->check);
	return (mask);
}

int	init_mutex(t_mutex *elem, int32_t count)
{
	int8_t	mask;

	mask = 0;
	elem->start = 0;
	elem->size = -1;
	elem->array = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (unsigned long)count);
	while (++elem->size < count)
	{
		if (pthread_mutex_init(&elem->array[elem->size], NULL))
		{
			mask = 1;
			break ;
		}	
	}
	if (pthread_mutex_init(&elem->print, NULL))
		mask += 2;
	if (pthread_mutex_init(&elem->number, NULL))
		mask += 4;
	if (pthread_mutex_init(&elem->check, NULL))
		mask += 8;
	if (mask)
		return (destroy_tmutex(elem, mask));
	return (0);
}
