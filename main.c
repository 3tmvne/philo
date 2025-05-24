#include "philo.h"

int main(int ac, char **av)
{   
    t_info info;
    t_philo *philos;
    int err = 0;

    info.num_philo = ft_atoi(av[1], &err);
    if(err)
        return (EXIT_FAILURE);
    philos = malloc(sizeof(t_philo) * info.num_philo);
    if (!philos)
        return (EXIT_FAILURE);
    info.philos = philos;
    // handle_input(ac, av, &info);
    // printf("%d - %d - %d - %d - %d\n", info.num_philo, info.time_to_die, info.time_to_eat, info.time_to_sleep, info.num_must_eat);
    // init_philo(&info, philos);
    // printf("%d\n" , info.philos[3].philo_id);
    // philosophers(&info);
    free(philos);
}