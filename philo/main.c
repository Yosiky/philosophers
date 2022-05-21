/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:32:09 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/20 22:45:31 by eestelle         ###   ########.fr       */
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

int	parser(t_data *res, int argc char **argv)
{
	int	error;

	error = ee_atoi(argv[1], 
}

int	main(int argc, char **argv)
{
	int	arg[6];

	if (argc == 5 || argc == 6)
	{
		while (--argc)
		{
			int	value = ee_atoi(argv[argc], arg + argc);
			printf("%d = %s, %d\n", argc, argv[argc], value);
			if (value)
				return (error(TEXT"Arguments not valid"));
		}
		if (arg[1] > 1)
			start_philo(arg);
		else
		{
			write(1, "Hello", 5);
			return (error(TEXT"Count philophers not valid"RESET));
		}
	}
	else
		return (error(TEXT"Count arguments is not equal 5 or 6"RESET));
	return (0);
}
