#ifndef PHILO_H
# define PHILO_H
# define ERROR ""
# define END "\n"
# define PRINT_ERROR(value) ERROR value END

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>


typedef struct s_philo_param
{
    int count;
    int time_sleep;
    int time_eat;
    int time_live;
    int count_eat;
    int flag_eat;
}   t_philo_param;

int     ee_atoi(const char *str);
void    ee_error(const char *str);
void    philo_param_init(t_philo_param *params, int argc, char **argv);


#endif // PHILO_H