#include "philo.h"

long     time_now(t_info *info)
{
    long    res;
    res = get_time_ms() - info->start_time;
    return res;
}

void    *routine(void *par)
{
    t_philo *philo = (t_philo*)par;
    t_info  *info = philo->data;
    while(1)
    {
        pthread_mutex_lock(&info->print_mutex);
        printf("%ld %d is thinking\n", time_now(info), philo->philo_id);
        pthread_mutex_unlock(&info->print_mutex);
        if(philo->philo_id % 2 != 0)
        {
            pthread_mutex_lock(philo->left_fork);
            printf("%ld %d has taken a fork\n", time_now(info), philo->philo_id);
            pthread_mutex_lock(philo->right_fork);
            printf("%ld %d has taken a fork\n", time_now(info), philo->philo_id);
        }
        else
        {
            pthread_mutex_lock(philo->left_fork);
            printf("%ld %d has taken a fork\n", time_now(info), philo->philo_id);
            pthread_mutex_lock(philo->right_fork);
            printf("%ld %d has taken a fork\n", time_now(info), philo->philo_id);
        }
        printf("%ld %d is eating\n", time_now(info), philo->philo_id);
        usleep(info->time_to_eat * 1000);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        pthread_mutex_lock(&info->print_mutex);
        printf("%ld %d is sleeping\n", time_now(info),philo->philo_id);
        usleep(info->time_to_sleep * 1000);
        pthread_mutex_unlock(&info->print_mutex);
        break;
    }
    return NULL;
}

void   philosophers(t_info *info)
{
    int i = 0;
    info->start_time = get_time_ms();
    while(i < info->num_philo)
    {
        info->start_time = get_time_ms();
        pthread_create(&info->philos[i].thread, NULL, routine, &info->philos[i]);
        i++;
    }
    i = 0;
    while(i < info->num_philo)
    {
        pthread_join(info->philos[i].thread, NULL);
        i++;
    }
}
