/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:32:09 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/29 12:36:25 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#ifdef __APPLE__

void	ft_usleep(useconds_t n)
{
	struct timeval	start;
	struct timeval	step;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&step, NULL);
		if ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
((size_t)(step.tv_usec - start.tv_usec))) > n)
			break ;
	}
}

#else

void	ft_usleep(useconds_t usec)
{
	usleep(usec);
}

#endif


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

int	error(const char *str)
{
	ee_putstr(2, ERROR "ERROR: " RESET);
	ee_putstr(2, str);
	return (1);
}

void	*philo_live_one(void *arg);
void	*philo_live_two(void *arg);

int	start_philo(t_params_philo *param)
{
	pthread_t	*tid;

	tid = (pthread_t *)malloc(sizeof(pthread_t) * param->number_of_philo);
	if (pthread_mutex_init(get_mutex_print(), NULL))
		return (1);
    if (init_mutex(get_mutex_array(), param->number_of_philo))
        return (1);
	get_time_start_work();
	for (int i = 0; i < param->number_of_philo; i += 2)
	{
		pthread_create(&tid[i], NULL, philo_live_one, NULL);
		pthread_detach(tid[i]);
	}
	for (int i = 1; i < param->number_of_philo; i += 2)
	{
		pthread_create(&tid[i], NULL, philo_live_two, NULL);
		pthread_detach(tid[i]);
	}
	while(1) ;
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
	return (param->number_of_philo <= 1 || param->time_to_die <= 0 || param->time_to_eat <= 0 || param->time_to_sleep <= 0
			|| (param->flag && param->number_of_times_each_philo_must_eat <= 0));
}


void	*philo_live_one(__attribute__((unused))void *arg)
{
	static t_params_philo	*param;
	static t_mutex			*mutex;
	static int				flag = 1;
	uint32_t				i;
	int32_t					count;
	
	count = 0;
	pthread_mutex_lock(get_mutex_print());
	if (flag) {
		param = get_param_philo();
		mutex = get_mutex_array();
		--flag;
	}
	i = get_number_philo_one();

	pthread_mutex_unlock(get_mutex_print());
	while (1)
	{
		pthread_mutex_lock(mutex->array + i % param->number_of_philo);
		philo_say(i, "has take a fork 0\n");
		pthread_mutex_lock(mutex->array + (i + 1) % param->number_of_philo);
		philo_say(i, "has take a fork 1\n");
		philo_say(i, "is eating\n");
		++count;
		ft_usleep(param->time_to_eat);
		pthread_mutex_unlock(mutex->array + i % param->number_of_philo);
		pthread_mutex_unlock(mutex->array + (i + 1) % param->number_of_philo);
		philo_say(i, "is sleeping\n");
		ft_usleep(param->time_to_sleep);
		if (param->flag && count == param->number_of_times_each_philo_must_eat)
		{
			philo_say(i, "died\n");
			return (0);
		}
		else
			philo_say(i, "is thinking\n");
	}
}

void	*philo_live_two(__attribute__((unused))void *arg)
{
	static t_params_philo	*param;
	static t_mutex			*mutex;
	static int				flag = 1;
	uint32_t				i;
	int32_t					count;
	
	count = 0;
	pthread_mutex_lock(get_mutex_print());
	if (flag) {
		param = get_param_philo();
		mutex = get_mutex_array();
		--flag;
	}
	i = get_number_philo_two();
	pthread_mutex_unlock(get_mutex_print());
	while (1)
	{
		pthread_mutex_lock(mutex->array + (i + 1) % param->number_of_philo);
		pthread_mutex_lock(mutex->array + i % param->number_of_philo);
		philo_say(i, "has take a fork 1\n");
		philo_say(i, "has take a fork 0\n");
		philo_say(i, "is eating\n");
		++count;
		usleep(param->time_to_eat);
		pthread_mutex_lock(mutex->array + (i + 1) % param->number_of_philo);
		pthread_mutex_lock(mutex->array + i % param->number_of_philo);
		philo_say(i, "is sleeping\n");
		usleep(param->time_to_sleep);
		if (param->flag && count == param->number_of_times_each_philo_must_eat)
		{
			philo_say(i, "died\n");
			return (0);
		}
		else
			philo_say(i, "is thinking\n");
	}
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
