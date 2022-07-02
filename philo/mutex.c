/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:37:21 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/29 12:33:31 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t *get_mutex_print(void)
{
	static pthread_mutex_t	mutex;

	return (&mutex);
}

pthread_mutex_t *get_mutex_for_number(void)
{
	static pthread_mutex_t	mutex;

	return (&mutex);
}

t_mutex	*get_mutex_array(void)
{
    static t_mutex	mutex;

    return (&mutex);
}

void	destroy_mutex(t_mutex *arr)
{
    uint32_t	i;

    i = -1;
    while (++i < arr->size)
        pthread_mutex_destroy(&arr->array[i]);
	free(arr->array);
}

int	init_mutex(t_mutex *arr, uint32_t count)
{
    arr->size = -1;
    arr->count = 0;
    arr->array = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
    while (++arr->size < count)
    {
        if (pthread_mutex_init(&arr->array[arr->size], NULL))
        {
            destroy_mutex(arr);
            return (1);
        }
    }
    return (0);
}