/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:31:52 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 13:55:26 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_params_philo *param)
{
	ee_putstr(1, INFO"Parameters for philosophers:\n");
	ee_putstr(1, "\tNumber of philosophers: "TEXT);
	ee_putnbr(1, param->number_of_philo);
	ee_putstr(1, INFO"\n\tTime to die: "TEXT);
	ee_putnbr(1, param->time_to_die);
	ee_putstr(1, INFO"\n\tTime to eat: "TEXT);
	ee_putnbr(1, param->time_to_eat);
	ee_putstr(1, INFO"\n\tTime to sleep: "TEXT);
	ee_putnbr(1, param->time_to_sleep);
	if (param->flag)
	{
		ee_putstr(1, INFO"\n\tNumber of times eahe philospher must eat: "TEXT);
		ee_putnbr(1, param->number_of_times_each_philo_must_eat);
	}
	ee_putstr(1, "\n"RESET);
}
