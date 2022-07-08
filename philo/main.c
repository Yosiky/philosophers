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

int32_t	get_number_philo_one(void)
{
	static int32_t	i = 1;

	i += 2;
	return (i - 2);
}

int32_t	get_number_philo_two(void)
{
	static int32_t	i = 2;

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

void	*philo_live_one(__attribute__((unused))void *arg)
{
	static t_params_philo	*param;
	static t_mutex			*mutex;
	static int				flag = 1;
	t_philo					philo;

	philo.count = 0;
	if (flag) {
		param = get_param_philo();
		mutex = get_mutex_struct();
		--flag;
	}
	pthread_mutex_lock(&mutex->number);
	philo.left = get_number_philo_one() % param->number_of_philo;
	philo.right = (philo.left + 1) % param->number_of_philo;
	philo.flag = &(*get_flag_philo())[philo.left - 1];
	philo.last = *get_time_start_work();
	pthread_mutex_unlock(&mutex->number);
	while (1)
	{
		pthread_mutex_lock(&mutex->check);
		if (*philo.flag)
		{
			pthread_mutex_unlock(&mutex->check);
			break ;
		}
		pthread_mutex_unlock(&mutex->check);
		pthread_mutex_lock(mutex->array + philo.left);
		philo_say(&philo, "has take a fork 0\n");
		pthread_mutex_lock(mutex->array + philo.right);
		philo_say(&philo, "has take a fork 1\n");
		gettimeofday(&philo.t, NULL);
		philo.diff = (philo.t.tv_sec - philo.last.tv_sec) * 1000000 + (philo.t.tv_usec - philo.last.tv_usec);
		if (philo.diff > param->time_to_die)
		{
			philo_say(&philo, "died\n");
			pthread_mutex_lock(&mutex->check);
			*philo.flag = 1;
			pthread_mutex_unlock(&mutex->check);
			pthread_mutex_unlock(mutex->array + philo.right);
			pthread_mutex_unlock(mutex->array + philo.left);
			break ;
		}
		philo.last = philo.t;
		philo_say(&philo, "is eating\n");
		++philo.count;
		usleep((useconds_t)param->time_to_eat);
		pthread_mutex_unlock(mutex->array + philo.right);
		pthread_mutex_unlock(mutex->array + philo.left);
		philo_say(&philo, "is sleeping\n");
		usleep((useconds_t)param->time_to_sleep);
		if (*philo.flag && philo.count == param->number_of_times_each_philo_must_eat)
			return (0);
		else
			philo_say(&philo, "is thinking\n");
	}
	return (NULL);
}

void	*philo_live_two(__attribute__((unused))void *arg)
{
	static t_params_philo	*param;
	static t_mutex			*mutex;
	static int				flag = 1;
	t_philo					philo;

	philo.count = 0;
	if (flag) {
		param = get_param_philo();
		mutex = get_mutex_struct();
		--flag;
	}
	pthread_mutex_lock(&mutex->number);
	philo.left = get_number_philo_two() % param->number_of_philo;
	philo.right = (philo.left + 1) % param->number_of_philo;
	philo.flag = &(*get_flag_philo())[philo.left - 1];
	philo.last = *get_time_start_work();
	pthread_mutex_unlock(&mutex->number);
	while (1)
	{
		pthread_mutex_lock(&mutex->check);
		if (*philo.flag)
		{
			pthread_mutex_unlock(&mutex->check);
			break ;
		}
		pthread_mutex_unlock(&mutex->check);
		pthread_mutex_lock(mutex->array + philo.right);
		philo_say(&philo, "has take a fork 1\n");
		pthread_mutex_lock(mutex->array + philo.left);
		philo_say(&philo, "has take a fork 0\n");
		gettimeofday(&philo.t, NULL);
		philo.diff = (philo.t.tv_sec - philo.last.tv_sec) * 1000000 + (philo.t.tv_usec - philo.last.tv_usec);
		if (philo.diff > param->time_to_die)
		{
			philo_say(&philo, "died\n");
			pthread_mutex_lock(&mutex->check);
			*philo.flag = 1;
			pthread_mutex_unlock(&mutex->check);
			pthread_mutex_unlock(mutex->array + philo.left);
			pthread_mutex_unlock(mutex->array + philo.right);
			break ;
		}
		philo.last = philo.t;
		philo_say(&philo, "is eating\n");
		++philo.count;
		usleep((useconds_t)param->time_to_eat);  
		pthread_mutex_unlock(mutex->array + philo.left);
		pthread_mutex_unlock(mutex->array + philo.right);
		philo_say(&philo, "is sleeping\n");
		usleep((useconds_t)param->time_to_sleep);
		if (*philo.flag && philo.count == param->number_of_times_each_philo_must_eat)
			return (0);
		else
			philo_say(&philo, "is thinking\n");
	}
	return (NULL);
}

int	start_philo(t_params_philo *param)
{
	pthread_t		*tid;
	static int32_t	flag = 0;
	uint8_t			**arr;
	pthread_mutex_t	*check;

	arr = get_flag_philo();
	tid = (pthread_t *)malloc(sizeof(pthread_t) * (unsigned long)param->number_of_philo);
	*arr = (uint8_t *)malloc(sizeof(uint8_t) * (unsigned long)param->number_of_philo);
	if (*arr == NULL || tid == NULL || init_mutex(get_mutex_struct(), param->number_of_philo))
	{
		error(TEXT"errro"RESET);
		free(*arr);
		free(tid);
		return (1);
	}
	pthread_mutex_lock(&get_mutex_struct()->number);
	pthread_mutex_unlock(&get_mutex_struct()->number);
	check = &get_mutex_struct()->check;
	ft_memset((void *)(*arr), 0, (size_t)param->number_of_philo);
	gettimeofday(get_time_start_work(), NULL);
	for (int i = 0; i < param->number_of_philo; i += 2)
		pthread_create(&tid[i], NULL, philo_live_one, NULL);
	for (int i = 1; i < param->number_of_philo; i += 2)
		pthread_create(&tid[i], NULL, philo_live_two, NULL);
	flag = 0;
	while(1)
	{
		pthread_mutex_lock(check);
		if ((*arr)[flag])
		{
			ft_memset((void *)(*arr), 1, (size_t)param->number_of_philo);
			pthread_mutex_unlock(check);
			for (int i = 0; i < param->number_of_philo; ++i)
				pthread_join(tid[i], NULL);
			break;
		}
		else
			pthread_mutex_unlock(check);
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
