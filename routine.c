#include "philo.h"

static int  should_stop(t_info *info)
{
    int result;
    
    pthread_mutex_lock(&info->death_mutex);
    result = info->someone_died || info->all_eaten;
    pthread_mutex_unlock(&info->death_mutex);
    return result;
}

static void eat(t_philo *philo)
{
    t_info *info = philo->data;
    
    if (philo->philo_id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, "has taken a fork");
    }
    if (should_stop(info))
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return;
    }
    pthread_mutex_lock(&info->meal_mutex);
    philo->last_meal = get_time_ms();
    philo->nb_eaten++;
    pthread_mutex_unlock(&info->meal_mutex);
    print_status(philo, "is eating");
    usleep(info->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

static void sleep_and_think(t_philo *philo)
{
    t_info *info = philo->data;
    
    print_status(philo, "is sleeping");
    usleep(info->time_to_sleep * 1000);
    
    if (!should_stop(info))
        print_status(philo, "is thinking");
}

void    *routine(void *par)
{
    t_philo *philo = (t_philo*)par;
    t_info *info = philo->data;
    
    if (philo->philo_id % 2 == 0)
        usleep(info->time_to_eat * 500);
    
    while (!should_stop(info))
    {
        eat(philo);
        if (should_stop(info))
            break;
        sleep_and_think(philo);
    }
    return NULL;
}

void    *monitor_death(void *par)
{
    t_info *info = (t_info*)par;
    
    while (!should_stop(info))
    {
        if (check_death(info))
            break;
        usleep(1000);
    }
    return NULL;
}

void    philosophers(t_info *info)
{
    int i = 0;
    pthread_t monitor;
    
    while(i < info->num_philo)
    {
        pthread_create(&info->philos[i].thread, NULL, routine, &info->philos[i]);
        i++;
    }
    
    pthread_create(&monitor, NULL, monitor_death, info);
    pthread_join(monitor, NULL);
    
    i = 0;
    while(i < info->num_philo)
    {
        pthread_join(info->philos[i].thread, NULL);
        i++;
    }
}
