#include "philo.h"

void    ee_error(const char *str)
{
    write(1, str, strlen(str));
    exit(-1);
}