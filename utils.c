#include "philo.h"

int ft_atoi(char *str, int *err)
{
    int result;
    int i;

    i = 0;
    result = 0;
    while(str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if(str[i] < '0' && str[i] > '9')
        *err = 1;
    return result;
}

