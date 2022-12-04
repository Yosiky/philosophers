#include "philo.h"
#include <stdio.h>

void    philo_param_init(t_philo_param *params, int argc, char **argv)
{
    int check_values = 0;

    params->count = ee_atoi(argv[0]);
    params->time_live = ee_atoi(argv[1]);
    params->time_eat = ee_atoi(argv[2]);
    params->time_sleep = ee_atoi(argv[3]);
    if (argc == 5)
    {
        params->count_eat = ee_atoi(argv[4]);
        params->flag_eat = 1;
    }
    else
        params->flag_eat = 0;
    check_values += params->count <= 1 ? 1 : 0;
    check_values += params->time_live <= 0 ? 2 : 0;
    check_values += params->time_sleep <= 0 ? 4 : 0;
    check_values += params->time_eat <= 0? 8 : 0;
    if (check_values)
        ee_error(PRINT_ERROR("not valid arguments"));
}

void    philo()