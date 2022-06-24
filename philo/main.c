/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:32:09 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 21:09:06 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(const char *str)
{
	ee_putstr(2, ERROR "ERROR: " RESET);
	ee_putstr(2, str);
	return (1);
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
			free(arr->array);
			return (1);
		}
	}
	return (0);
}

int	start_philo(t_params_philo *param)
{
	t_mutex	*arr;

	arr = get_mutex_array();
	return (init_mutex(arr, param->number_of_philo));
}

int	init_param(t_params_philo *dst, int size, char **str)
{
	int	error;

	error = ee_atoi(str[0], &dst->number_of_philo);
	error += ee_atoi(str[1], &dst->time_to_die);
	error += ee_atoi(str[2], &dst->time_to_eat);
	error += ee_atoi(str[3], &dst->time_to_sleep);
	dst->flag = 0;
	if (size == 5)
	{
		error += ee_atoi(str[4], &dst->number_of_times_each_philo_must_eat);
		dst->flag = 1;
	}
	return (error);
}

int	check_param(t_params_philo *param)
{
	return (param->number_of_philo <= 1 || param->time_to_die <= 0 || param->time_to_eat <= 0 || param->time_to_sleep <= 0
			|| (param->flag && param->number_of_times_each_philo_must_eat <= 0));
}

void	philo_live_one(void)
{
	static const t_params_philo	*param = get_param_philo();
	static t_mutex				*mutex = get_mutex_array();
	static uint32_t				i = -1;
	struct timeval				t;

	++i;
	if (i % 2)
		usleep(10);
	while (1)
	{
		pthread_mutex_lock(arr + i);
		pthread_mutex_lock(arr + (i + 1) % param->size);
		gettimeofday(&t, NULL);
		usleep(param->
	}
	
}

int	main(int argc, char **argv)
{
	t_params_philo	param;

	get_time_start_work();
	init_mutex(get_mutex_print(), 1);
	if (argc == 5 || argc == 6)
	{
		if (init_param(&param, argc - 1, argv + 1))
			return (error(TEXT"Arguments not valid"));
		print_info(&param);
		if (!check_param(&param))
		{
			if (!start_philo(&param))
				return (0);
			else
				error(TEXT"Don't initial all mutex"RESET);
		}
		else
			return (error(TEXT"Count philophers not valid"RESET));
	}
	else
		return (error(TEXT"Count arguments is not equal 5 or 6"RESET));
	return (0);
}
