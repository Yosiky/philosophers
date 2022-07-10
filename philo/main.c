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

int	error(const char *str)
{
	ee_putstr(2, ERROR "ERROR: " RESET);
	ee_putstr(2, str);
	return (1);
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
	else
		dst->number_of_times_each_philo_must_eat = -1;
	return (error);
}

int	check_param(t_params_philo *param)
{
	return (param->number_of_philo < 1 || param->time_to_die <= 0
		|| param->time_to_eat <= 0 || param->time_to_sleep <= 0
		|| (param->flag
			&& param->number_of_times_each_philo_must_eat <= 0));
}

void	kostily(t_params_philo *param)
{
	t_philo	philo;

	pthread_mutex_init(&get_mutex_struct()->check, NULL);
	pthread_mutex_init(&get_mutex_struct()->print, NULL);
	gettimeofday(get_time_start_work(), NULL);
	philo.number = 1;
	philo_say(&philo, "has take a fork 0\n");
	ft_usleep((useconds_t)param->time_to_die);
	philo_say(&philo, "died\n");
	pthread_mutex_destroy(&get_mutex_struct()->check);
	pthread_mutex_destroy(&get_mutex_struct()->print);
}

int	main(int argc, char **argv)
{
	t_params_philo	*param;

	param = get_param_philo();
	if (argc == 5 || argc == 6)
	{
		if (init_param(param, argc - 1, argv + 1))
			return (error(TEXT"Arguments not valid"RESET));
		print_info(param);
		if (!check_param(param))
		{
			if (param->number_of_philo == 1)
				kostily(param);
			else if (!start_philo(param))
				return (0);
			else
				error(TEXT"Don't init something)"RESET);
		}
		else
			return (error(TEXT"Count philophers not valid"RESET));
	}
	else
		return (error(TEXT"Count arguments is not equal 5 or 6"RESET));
	return (0);
}
