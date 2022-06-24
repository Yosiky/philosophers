/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:31:52 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 13:52:11 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_params_philo *param)
{
	ee_putstr(1, INFO"Parameters for philosophers:\n");
	ee_putstr(1, "Number of philosophers: ");
	ee_putnbr(1, param->number_of_philo);
	ee_putstr(1, "\nTime to die: ");
	ee_putnbr(1, param->time_to_die);
	ee_putstr(1, "\nTime to eat: ");
	ee_putnbr(1, param->time_to_eat);
	ee_putstr(1, "\nTime to sleep: ");
	ee_putnbr(1, param->time_to_sleep);
	if (param->flag)
	{
		ee_putstr(1, "\nNumber of times eahe philospher must eat: ");
		ee_putnbr(1, param->number_of_times_each_philo_must_eat);
	}
	ee_putstr(1, "\n"RESET);
}
