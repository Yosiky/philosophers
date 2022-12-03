#include "philo.h"

void    start_programm(t_philo_param *params)
{

    


}

int main(int argc, char **argv)
{
    t_philo_param   params;

    if (argc != 5 && argc != 6)
        ee_error(PRINT_ERROR("not valid count arguments"));
        
    philo_param_init(&params, argc - 1, argv + 1);
    start_programm(&params);
    return (0);
}