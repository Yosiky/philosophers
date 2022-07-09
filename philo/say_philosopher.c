/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   say_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:31:05 by eestelle          #+#    #+#             */
/*   Updated: 2022/07/03 21:09:21 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval	*get_time_start_work(void)
{
	static struct timeval	t;

	return (&t);
}

static int32_t	ee_itoa(int64_t value, char *str)
{
	int64_t	copy;
	char	arr[30];
	int32_t	len;
	int32_t	i;

	copy = value;
	len = 0;
	if (copy < 0)
	{
		*(str++) = '-';
		copy *= -1;
	}
	while (copy > 0)
	{
		arr[len++] = '0' + copy % 10;
		copy /= 10;
	}
	i = -1;
	while (++i < len)
		str[i] = arr[len - i - 1];
	if (value == 0)
		str[len++] = '0';
	return (len + (value < 0));
}

static int32_t	ee_strcpy(char *dst, char *src)
{
	int32_t	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	return (i);
}

void	swap(char *line)
{
	line[3] = line[2];
	line[2] = line[1];
	line[1] = line[0];
	line[0] = '.';
}

void	philo_say(t_philo *philo, char *str)
{
	static int8_t			flag = 0;
	static char				line[100];
	static int32_t			i;

	pthread_mutex_lock(&get_mutex_struct()->print);
	if (flag)
	{
		pthread_mutex_unlock(&get_mutex_struct()->print);
		return ;
	}
	if (str[0] == 'd')
		flag = 1;
	gettimeofday(&philo->t, NULL);
	i = ee_itoa((philo->t.tv_sec - get_time_start_work()->tv_sec) * 1000000
			+ (philo->t.tv_usec - get_time_start_work()->tv_usec), line);
	line[i++] = ' ';
	i += ee_itoa(philo->number, line + i);
	line[i++] = ' ';
	i += ee_strcpy(line + i, (char *)str);
	pthread_mutex_lock(&get_mutex_struct()->check);
	if (*philo->flag != 1)
		write(1, line, (size_t)i);
	pthread_mutex_unlock(&get_mutex_struct()->check);
	pthread_mutex_unlock(&get_mutex_struct()->print);
}
