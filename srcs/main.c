#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: ./philo number_of_philosophers time_to_die ", 1);
		ft_putstr_fd("time_to_eat time_to_sleep ", 1);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 1);
		return (ERROR);
	}
	if (check_input(argc, argv) == 1)
		return (ERROR);
	if (!init_data(&data, argc, argv))
		return (exit_with_error("Error: Failed to initialize data\n", 2));
	if (!init_mutexes(&data) || !init_philos(&data) || !init_threads(&data))
	{
		clean_up(&data);
		return (ERROR);
	}
	pthread_join(data.monitor_thread, NULL);
	clean_up(&data);
	return (SUCCESS);
}
