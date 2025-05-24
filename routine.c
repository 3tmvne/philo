#include "philo.h"

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_info  *info = philo->data;

    while(!info->someone_died)
    {
        if(info->num_must_eat > 0 && philo->nb_eaten >= info->num_must_eat)
            break;
        pthread_mutex_lock(&info->print_mutex);
        printf("%d is thinking\n", philo->philo_id);
        pthread_mutex_unlock(&info->print_mutex);

        if (philo->philo_id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            printf("%d has taken a fork\n", philo->philo_id);
            pthread_mutex_lock(philo->right_fork);
            printf("%d has taken a fork\n", philo->philo_id);
        }
        else
        {
            pthread_mutex_lock(philo->left_fork);
            printf("%d has taken a fork\n", philo->philo_id);
            pthread_mutex_lock(philo->right_fork);
            printf("%d has taken a fork\n", philo->philo_id);
        }
        pthread_mutex_lock(&info->print_mutex);
        printf("%d is eating\n", philo->philo_id);
        pthread_mutex_unlock(&info->print_mutex);

        philo->last_meal = get_time_ms();
        philo->nb_eaten++;
        usleep(info->time_to_eat * 1000);

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        pthread_mutex_lock(&info->print_mutex);
        printf("%d is sleeping\n", philo->philo_id);
        pthread_mutex_unlock(&info->print_mutex);

        usleep(info->time_to_sleep * 1000);

    }
    return NULL;
}

void *monitor(void *arg)
{
    t_info *info = (t_info *)arg;
    int i;

    while (!info->someone_died)
    {
        i = 0;
        while (i < info->num_philo)
        {
            if (get_time_ms() - info->philos[i].last_meal > info->time_to_die)
            {
                pthread_mutex_lock(&info->print_mutex);
                printf("%d died\n", info->philos[i].philo_id);
                pthread_mutex_unlock(&info->print_mutex);
                info->someone_died = 1;
                break;
            }
            i++;
        }
        usleep(1000);
    }
    return NULL;
}

void   philosophers(t_info *info)
{
    pthread_t monitor_thread;
    int i = 0;

    while(i < info->num_philo)
    {
        pthread_create(&monitor_thread, NULL, monitor, info);
        pthread_detach(monitor_thread);
        pthread_create(&info->philos[i].thread, NULL, routine, &info->philos[i]);
        pthread_join(info->philos[i].thread, NULL);
        i++;
    }
}