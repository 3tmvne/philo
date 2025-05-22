#include "philo.h"

int main(int ac, char **av)
{   
    t_info info;
    t_philo *philos;

    philos = malloc(sizeof(t_philo) * (ac - 1));
    info.philos = philos;
    handle_input(ac - 1, av, &info);
    // printf("%d - %d - %d - %d - %d\n", info.num_philo, info.time_to_die, info.time_to_eat, info.time_to_sleep, info.num_must_eat);
    init_philo(&info, philos);
    // printf("%d\n" , info.philos[3].philo_id);
    
}