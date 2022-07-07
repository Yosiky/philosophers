/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eestelle <eestelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:59:29 by eestelle          #+#    #+#             */
/*   Updated: 2022/07/03 21:08:23 by eestelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>

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

typedef struct s_philo
{
	int32_t		left;
	int32_t		right;
	int32_t		count;
	uint8_t		*flag;
	struct timeval	t;
	struct timeval	last;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	*array;
	int32_t			size;
	pthread_mutex_t	print;
	pthread_mutex_t	number;
	pthread_mutex_t	check;
}	t_mutex;

int				ee_atoi(const char *str, int *ptr);
uint32_t		ee_strlen(const char *str);
int32_t			ee_putstr(int fd, const char *str);
int32_t			ee_putnbr(int fd, const int32_t n);
void			philo_say(int number_philo, char *str);
void			print_info(t_params_philo *param);
t_mutex 		*get_mutex_struct(void);
void	        destroy_mutex(t_mutex *arr);
int	            init_mutex(t_mutex *arr, int32_t count);
struct timeval	*get_time_start_work(void);
void	*ft_memset(void *s, int c, size_t n);
uint8_t		**get_flag_philo(void);
#endif
