#include "philo.h"

int main(int ac, char **av)
{   
    t_info info;
    t_philo *philos;

    handle_input(ac, av, &info);
    philos = malloc(sizeof(t_philo) * info.num_philo);
    if (!philos)
        return (EXIT_FAILURE);
    info.philos = philos;
    init_philo(&info, philos);
    philosophers(&info);
    free(philos);
    return 0;
}