#ifndef	PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stddef.h>
# include <unistd.h>
# include "color.h"

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

#endif
