#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo t_philo;

typedef struct s_info
{
    int             num_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             num_must_eat;
    long            start_time;
    int             someone_died;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    t_philo  *philos;
}t_info;

typedef struct s_philo
{
    int             philo_id;
    int             nb_eaten;
    long            last_meal;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_info          *data;
}t_philo;

void    handle_input(int ac, char **av, t_info *info);
int     ft_atoi(char *str, int *err);
void    init_philo(t_info *info, t_philo *philos);
void    philosophers(t_info *info);
long    get_time_ms(void);

#endif