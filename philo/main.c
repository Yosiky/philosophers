/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:32:09 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/27 14:23:32 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	error(const char *str)
{
	ee_putstr(2, ERROR "ERROR: " RESET);
	ee_putstr(2, str);
	return (1);
}

void	start_philo(int *arr)
{
	arr[0] = 0;
}

int	parser(t_input_data *arg, char **str)
{
	int	error;
	int	i;

	i = -1;
	error = 0;
	while (++i < 4 + arg->flag)
		error += ee_atoi(str[i], arg->data + i);
	return (error);	
}

int	main(int argc, char **argv)
{
	t_input_data	arg;

	if (argc == 5)
		arg.flag = 0;
	else if (argc == 6)
		arg.flag = 1;
	else
		return (error(TEXT"Count arguments is not equal 5 or 6"RESET));
	if (parser(&arg, argv + 1))
		return (error(ERROR"Invalid arguments"RESET));
	return (0);
}
