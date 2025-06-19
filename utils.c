#include "philo.h"

int ft_atoi(char *str, int *err)
{
    int result;
    int i;

    i = 0;
    result = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] < '0' || str[i] > '9')
    {
        *err = 1;
        return 0;
    }    
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] != '\0')
        *err = 1;
    return result;
}

void    print_status(t_philo *philo, char *status)
{
    t_info *info = philo->data;
    long timestamp;
    
    pthread_mutex_lock(&info->death_mutex);
    if (info->someone_died)
    {
        pthread_mutex_unlock(&info->death_mutex);
        return;
    }
    pthread_mutex_unlock(&info->death_mutex);
    
    pthread_mutex_lock(&info->print_mutex);
    timestamp = get_time_ms() - info->start_time;
    printf("%ld %d %s\n", timestamp, philo->philo_id, status);
    pthread_mutex_unlock(&info->print_mutex);
}

int check_death(t_info *info)
{
    int i = 0;
    long current_time;
    int all_eaten = 1;
    
    while (i < info->num_philo)
    {
        pthread_mutex_lock(&info->meal_mutex);
        current_time = get_time_ms();
        
        // Check if philosopher died
        if (current_time - info->philos[i].last_meal > info->time_to_die)
        {
            pthread_mutex_unlock(&info->meal_mutex);
            pthread_mutex_lock(&info->death_mutex);
            info->someone_died = 1;
            pthread_mutex_unlock(&info->death_mutex);
            
            pthread_mutex_lock(&info->print_mutex);
            printf("%ld %d died\n", current_time - info->start_time, info->philos[i].philo_id);
            pthread_mutex_unlock(&info->print_mutex);
            return 1;
        }
        
        // Check if all philosophers have eaten enough
        if (info->num_must_eat != -1 && info->philos[i].nb_eaten < info->num_must_eat)
            all_eaten = 0;
            
        pthread_mutex_unlock(&info->meal_mutex);
        i++;
    }
    
    // If all philosophers have eaten enough times
    if (info->num_must_eat != -1 && all_eaten)
    {
        pthread_mutex_lock(&info->death_mutex);
        info->all_eaten = 1;
        pthread_mutex_unlock(&info->death_mutex);
        return 1;
    }
    
    return 0;
}

void cleanup(t_info *info)
{
    int i = 0;
    
    while (i < info->num_philo)
    {
        pthread_mutex_destroy(&info->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&info->print_mutex);
    pthread_mutex_destroy(&info->death_mutex);
    pthread_mutex_destroy(&info->meal_mutex);
    free(info->forks);
}