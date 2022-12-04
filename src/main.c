#include "philo.h"

pthread_mutex_t *mutexs;


void    start_programm(t_philo_param *params)
{
    for (int i = 0; i < params->count; ++i)
        philo(params, i);
}

int main(int argc, char **argv)
{
    t_philo_param   params;

    if (argc != 5 && argc != 6)
        ee_error(PRINT_ERROR("not valid count arguments"));
    mutexs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (params->count + 1));
    if (mutexs == NULL)
        ee_error(PRINT_ERROR("cannot malloc array mutex"));
    philo_param_init(&params, argc - 1, argv + 1);
    start_programm(&params);
    return (0);
}
