#include "philo.h"

int ee_atoi(const char *str)
{
    int ans = atoi(str);
    
    for (int i = 0; str[i]; ++i)
        if (!isdigit(str[i]))
            ee_error(PRINT_ERROR("not valid string in atoi"));
    return (ans);
}