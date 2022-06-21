#ifndef	PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stddef.h>
# include <unistd.h>
# include "color.h"

<<<<<<< HEAD:philo/philo.h
typedef struct s_input_data
{
	int	flag;
	int	data[5];
}	t_input_data;

int		ee_atoi(const char *str, int *ptr);
int		ee_strlen(const char *str);
int		ee_putstr(int fd, const char *str);
int		ee_putnbr(int fd, const int value);
void	philo_say(int i, const char *str);
=======
typedef	struct s_params_philo
{
	int32_t	number_of_philo;
	int32_t	time_to_die;
	int32_t	time_to_eat;
	int32_t	time_to_sleep;
	int32_t	number_of_times_each_philo_must_eat;
	int32_t	flag;
}	t_params_philo;

int	ee_atoi(const char *str, int *ptr);
int	ee_strlen(const char *str);
int	ee_putstr(int fd, const char *str);
>>>>>>> school_version:philo/inc/philo.h

#endif