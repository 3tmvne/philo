#include "philo.h"

static int     check_input(t_info *info, int ac)
{
    if (info->num_philo < 1
        || info->time_to_die < 1
        || info->time_to_eat < 1
        || info->time_to_sleep < 1
        || (ac == 5 && info->num_must_eat < 1))
        return 0;
    return 1;
}

void    handle_input(int ac, char **av, t_info *info)
{
    int err;

    err = 0;
    if(ac == 5 || ac == 6)
    {
        info->num_philo = ft_atoi(av[1], &err);
        info->time_to_die = ft_atoi(av[2], &err);
        info->time_to_eat = ft_atoi(av[3], &err);
        info->time_to_sleep = ft_atoi(av[4], &err);
        info->num_must_eat = -1;
        if(ac == 6)
            info->num_must_eat = ft_atoi(av[5], &err);
        if (err)
            exit(EXIT_FAILURE);
    }
    else
        exit(EXIT_FAILURE);
    if(!check_input(info, ac))
        exit(EXIT_FAILURE);
}
