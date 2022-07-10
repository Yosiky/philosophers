/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:23:43 by eestelle          #+#    #+#             */
/*   Updated: 2022/07/09 16:23:44 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_params_philo	*get_param_philo(void)
{
	static t_params_philo	param;

	return (&param);
}

int32_t	get_number_philo(void)
{
	static int32_t	i = 1;

	return (i++);
}

uint8_t	**get_flag_philo(void)
{
	static uint8_t	*i = NULL;

	return (&i);
}
