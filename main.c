#include "philo.h"

int main(int ac, char **av)
{   
    t_info  info;
    t_philo *philos;

    handle_input(ac, av, &info);
    if (info.num_philo == 1)
    {
        printf("0 1 has taken a fork\n");
        usleep(info.time_to_die * 1000);
        printf("%d 1 died\n", info.time_to_die);
        return 0;
    }
    philos = malloc(sizeof(t_philo) * info.num_philo);
    if (!philos)
        return (EXIT_FAILURE);
    info.philos = philos;
    init_philo(&info, philos);
    philosophers(&info);
    cleanup(&info);
    free(philos);
    return 0;
}