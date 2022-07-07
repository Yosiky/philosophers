/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:32:09 by eestelle          #+#    #+#             */
/*   Updated: 2022/07/03 21:13:33 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_params_philo	*get_param_philo(void)
{
	static t_params_philo	param;

	return (&param);
}

uint32_t	get_number_philo_one(void)
{
	static uint32_t	i = 1;

	i += 2;
	return (i - 2);
}

uint32_t	get_number_philo_two(void)
{
	static uint32_t	i = 2;

	i += 2;
	return (i - 2);
}

uint8_t		**get_flag_philo(void)
{
	static uint8_t	*i = NULL;

	return (&i);
}

int	error(const char *str)
{
	ee_putstr(2, ERROR "ERROR: " RESET);
	ee_putstr(2, str);
	return (1);
}

void	*philo_live(void *arg);

int	start_philo(t_params_philo *param)
{
	pthread_t	*tid;
	int32_t		flag;
	uint8_t		**arr;
	
	tid = (pthread_t *)malloc(sizeof(pthread_t) * param->number_of_philo);
	arr = get_flag_philo();
	*arr = (uint8_t *)malloc(sizeof(uint8_t) * param->number_of_philo);
	ft_memset((void *)(*arr), 0, param->number_of_philo);
	if (pthread_mutex_init(get_mutex_print(), NULL))
		return (1);
    if (init_mutex(get_mutex_array(), param->number_of_philo))
        return (1);
	gettimeofday(get_time_start_work(), NULL);
	for (int i = 0; i < param->number_of_philo; i += 2)
	{
		pthread_create(&tid[i], NULL, philo_live, (void *)1);
	}
	usleep(10);
	for (int i = 1; i < param->number_of_philo; i += 2)
	{
		pthread_create(&tid[i], NULL, philo_live, (void *)0);
	}
	flag = 0;
	while(1)
	{
		if ((*arr)[flag])
		{
			pthread_mutex_lock(get_mutex_for_number());
			ft_memset((void *)(*arr), 1, param->number_of_philo);
			for (int i = 0; i < param->number_of_philo; ++i)
				pthread_join(tid[i], NULL);
			pthread_mutex_unlock(get_mutex_for_number());
			break;
		}
		++flag;
		flag %= param->number_of_philo;
	}
	return (0);
}

int	init_param(t_params_philo *dst, int size, char **str)
{
	int	error;

	error = ee_atoi(str[0], &dst->number_of_philo);
	error += ee_atoi(str[1], &dst->time_to_die);
	error += ee_atoi(str[2], &dst->time_to_eat);
	error += ee_atoi(str[3], &dst->time_to_sleep);
	dst->time_to_die *= 1000;
	dst->time_to_eat *= 1000;
	dst->time_to_sleep *= 1000;
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
	return (param->number_of_philo < 1 || param->time_to_die <= 0 || param->time_to_eat <= 0 || param->time_to_sleep <= 0
			|| (param->flag && param->number_of_times_each_philo_must_eat <= 0));
}


void	*philo_live(__attribute__((unused))void *arg)
{
	static t_params_philo	*param;
	static t_mutex			*mutex;
	static int				flag = 1;
	uint32_t				i;
	int32_t					count;
	struct timeval			t;
	struct timeval			last;
	
	count = 0;
	pthread_mutex_lock(get_mutex_for_number());
	if (flag) {
		param = get_param_philo();
		mutex = get_mutex_array();
		--flag;
	}
	if ((int)arg)
		i = get_number_philo_one();
	else
		i = get_number_philo_two();
	last = *get_time_start_work();
	pthread_mutex_unlock(get_mutex_for_number());
	while (1)
	{
		pthread_mutex_lock(mutex->array + i % param->number_of_philo);
		philo_say(i, "has take a fork 0\n");
		pthread_mutex_lock(mutex->array + (i + 1) % param->number_of_philo);
		philo_say(i, "has take a fork 1\n");
		gettimeofday(&t, NULL);
		if ((*get_flag_philo())[i - 1])
		{
			pthread_mutex_unlock(mutex->array + i % param->number_of_philo);
			pthread_mutex_unlock(mutex->array + (i + 1) % param->number_of_philo);
			break ;
		}
		if (((t.tv_sec - last.tv_sec) * 1000000 + (t.tv_usec - last.tv_usec)) > param->time_to_die)
		{
			philo_say(i, "is die\n");
			(*get_flag_philo())[i - 1] = 1;
			pthread_mutex_unlock(mutex->array + i % param->number_of_philo);
			pthread_mutex_unlock(mutex->array + (i + 1) % param->number_of_philo);
			break ;
		}
		last = t;
		philo_say(i, "is eating\n");
		++count;
		usleep(param->time_to_eat);  
		pthread_mutex_unlock(mutex->array + i % param->number_of_philo);
		pthread_mutex_unlock(mutex->array + (i + 1) % param->number_of_philo);
		philo_say(i, "is sleeping\n");
		usleep(param->time_to_sleep);
		if (param->flag && count == param->number_of_times_each_philo_must_eat)
			return (0);
		else
			philo_say(i, "is thinking\n");
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_params_philo	*param;

	param = get_param_philo();
	if (argc == 5 || argc == 6)
	{
		if (init_param(param, argc - 1, argv + 1))
			return (error(TEXT"Arguments not valid"));
		print_info(param);
		if (!check_param(param))
		{
			if (!start_philo(param))
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
