/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:32:09 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 13:44:17 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(const char *str)
{
	ee_putstr(2, ERROR "ERROR: " RESET);
	ee_putstr(2, str);
	return (1);
}

pthread_mutex_t	**get_mutex_array(void)
{
	static pthread_mutex_t	*array;

	return (&array);
}

void	start_philo(__attribute__((unused))t_params_philo *param)
{
	int32_t		i;
	pthread_mutex_t	**arr;

	arr = get_mutex_array();
	*arr = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * param->number_of_philo);
	i = -1;
	while (++i < param->number_of_philo)
		pthread_mutex_init((*arr) + i, NULL);

	return ;
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

int	main(int argc, char **argv)
{
	t_params_philo	param;

	if (argc == 5 || argc == 6)
	{
		if (init_param(&param, argc - 1, argv + 1))
			return (error(TEXT"Arguments not valid"));
		if (param.number_of_philo > 1)
			start_philo(&param);
		else
			return (error(TEXT"Count philophers not valid"RESET));
		print_info(&param);
	}
	else
		return (error(TEXT"Count arguments is not equal 5 or 6"RESET));
	return (0);
}
