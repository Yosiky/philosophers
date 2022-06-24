/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:59:29 by eestelle          #+#    #+#             */
/*   Updated: 2022/06/24 20:54:49 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stddef.h>
# include <unistd.h>
# include <stdint.h>
# include <pthread.h>
# include "color.h"

# ifdef __linux__
#  include <malloc.h>
# else
#  include <stdlib.h>
# endif

typedef struct s_params_philo
{
	int32_t	number_of_philo;
	int32_t	time_to_die;
	int32_t	time_to_eat;
	int32_t	time_to_sleep;
	int32_t	number_of_times_each_philo_must_eat;
	int32_t	flag;
}	t_params_philo;

typedef struct s_mutex
{
	pthread_mutex_t	*array;
	uint32_t		size;
	uint32_t		count;
}	t_mutex;

int				ee_atoi(const char *str, int *ptr);
int				ee_strlen(const char *str);
int				ee_putstr(int fd, const char *str);
int				ee_putnbr(int fd, const int value);
void			philo_say(int i, const char *str);
void			print_info(t_params_philo *param);
pthread_mutex_t	*get_mutex_print(void);
struct timeval	*get_time_start_work(void);

#endif
