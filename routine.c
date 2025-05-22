#include "philo.h"

void    *routine()
{

}

void   philosophers(t_info *info)
{
    pthread_t thread;
    int i = 0;

    while(i < info->num_philo)
    {
        pthread_creat(info->philos[i].thread, NULL, routine, NULL);
        pthread_join(info->philos[i].thread, NULL);
        i++;
    }
}