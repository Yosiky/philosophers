/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ee_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle </var/spool/mail/eestelle>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:59:01 by eestelle          #+#    #+#             */
/*   Updated: 2022/05/20 13:00:22 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint32_t	ee_strlen(const char *str)
{
	uint32_t	size;

	if (str == NULL)
		return (0);
	size = 0;
	while (str[size])
		++size;
	return (size);
}
