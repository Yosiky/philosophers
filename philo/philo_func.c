/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:20:28 by eestelle          #+#    #+#             */
/*   Updated: 2022/07/09 16:20:29 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef unsigned long	t_ul;

void	philo_init(t_mutex **mut, t_params_philo **param, t_philo *philo)
{
	static int	flag = 1;

	pthread_mutex_lock(&get_mutex_struct()->number);
	if (flag)
	{
		*param = get_param_philo();
		*mut = get_mutex_struct();
		gettimeofday(get_time_start_work(), NULL);
		flag = 0;
	}
	philo->count = 0;
	philo->number = get_number_philo();
	philo->right = philo->number - 1;
	philo->left = philo->number % (*param)->number_of_philo;
	philo->flag = &(*get_flag_philo())[philo->left];
	philo->last = *get_time_start_work();
	pthread_mutex_unlock(&(*mut)->number);
}

void	philo_eat(t_params_philo *param, t_mutex *mutex, t_philo *philo)
{
	pthread_mutex_lock(mutex->array + philo->right);
	philo_say(philo, "has take a fork 0\n");
	pthread_mutex_lock(mutex->array + philo->left);
	philo_say(philo, "has take a fork 1\n");
	gettimeofday(&philo->t, NULL);
	philo->diff = (philo->t.tv_sec - philo->last.tv_sec) * 1000
		+ (philo->t.tv_usec - philo->last.tv_usec) / 1000;
	if (philo->diff > param->time_to_die / 1000
		|| philo->diff + param->time_to_eat / 1000 > param->time_to_die / 1000)
	{
		philo_say(philo, "died\n");
		pthread_mutex_lock(&mutex->check);
		*philo->flag = 1;
		pthread_mutex_unlock(&mutex->check);
	}
	philo_say(philo, "is eating\n");
	++philo->count;
	ft_usleep((useconds_t)param->time_to_eat);
	gettimeofday(&philo->last, NULL);
	pthread_mutex_unlock(mutex->array + philo->left);
	pthread_mutex_unlock(mutex->array + philo->right);
}

void	*philo_live(__attribute__((unused))void *arg)
{
	static t_params_philo	*param;
	static t_mutex			*mutex;
	t_philo					philo;

	philo_init(&mutex, &param, &philo);
	if (philo.number % 2 == 0)
		ft_usleep(500);
	while (1)
	{
		pthread_mutex_lock(&mutex->check);
		if (*philo.flag)
			break ;
		pthread_mutex_unlock(&mutex->check);
		philo_eat(param, mutex, &philo);
		philo_say(&philo, "is sleeping\n");
		ft_usleep((useconds_t)param->time_to_sleep);
		pthread_mutex_lock(&mutex->check);
		if (!*philo.flag)
			*philo.flag = 2
				* (philo.count == param->number_of_times_each_philo_must_eat);
		pthread_mutex_unlock(&mutex->check);
		philo_say(&philo, "is thinking\n");
	}
	pthread_mutex_unlock(&mutex->check);
	return (NULL);
}

void	monitor(t_params_philo *param, uint8_t *arr)
{
	static pthread_mutex_t	*check;
	static int32_t			i = 0;
	static int32_t			count = 0;

	check = &get_mutex_struct()->check;
	while (count != param->number_of_philo)
	{
		pthread_mutex_lock(check);
		if (arr[i] == 1)
		{
			ft_memset((void *)arr, 1, (size_t)param->number_of_philo);
			pthread_mutex_unlock(check);
			break ;
		}
		else if (arr[i] == 2)
			++count;
		else
			count = 0;
		pthread_mutex_unlock(check);
		++i;
		i %= param->number_of_philo;
	}
}

int	start_philo(t_params_philo *param)
{
	pthread_t		*tid;
	uint8_t			**arr;
	static int32_t	i = 0;

	arr = get_flag_philo();
	tid = (pthread_t *)malloc(sizeof(pthread_t) * (t_ul)param->number_of_philo);
	*arr = (uint8_t *)malloc(sizeof(uint8_t) * (t_ul)param->number_of_philo);
	if (*arr == NULL || tid == NULL
		|| init_mutex(get_mutex_struct(), param->number_of_philo))
	{
		free(*arr);
		free(tid);
		return (1);
	}	
	ft_memset((void *)(*arr), 0, (size_t)param->number_of_philo);
	while (i < param->number_of_philo)
	{
		pthread_create(&tid[i], NULL, philo_live, NULL);
		pthread_detach(tid[i++]);
	}
	monitor(param, *arr);
	free(*arr);
	free(tid);
	destroy_tmutex(get_mutex_struct(), (int8_t)0xff);
	return (0);
}
