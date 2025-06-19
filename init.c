#include "philo.h"

long    get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    init_philo(t_info *info, t_philo *philos)
{
    int i = 0;

    info->forks = malloc(sizeof(pthread_mutex_t) * info->num_philo);
    if (!info->forks)
        return;
    while (i < info->num_philo)
    {
        pthread_mutex_init(&info->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&info->print_mutex, NULL);
    pthread_mutex_init(&info->death_mutex, NULL);
    pthread_mutex_init(&info->meal_mutex, NULL);

    info->someone_died = 0;
    info->all_eaten = 0;
    info->start_time = get_time_ms();

    i = 0;
    while(i < info->num_philo) 
    {
        philos[i].philo_id = i + 1;
        philos[i].nb_eaten = 0;
        philos[i].last_meal = info->start_time;
        philos[i].left_fork = &info->forks[i];
        philos[i].right_fork = &info->forks[(i + 1) % info->num_philo];
        philos[i].data = info;
        i++;
    }
}