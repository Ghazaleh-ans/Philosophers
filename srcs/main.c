#include "../includes/philo.h"

int	check_digit_input(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0 || check_digit_input(argv[i]) == 1)
		{
			ft_putstr_fd("Invalid arguments.\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: ./philo number_of_philosophers time_to_die ", 2);
		ft_putstr_fd("time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
		return (ERROR);
	}
	if(check_input(argv) != 0)
		return (ERROR);
	if (!init_data(&data, argc, argv))
	{
		ft_putstr_fd("Error: Failed to initialize data\n", 2);
		return (ERROR);
	}
	if (!init_mutexes(&data) || !init_philos(&data) || !init_threads(&data))
	{
		clean_up(&data);
		return (ERROR);
	}
	pthread_join(data.monitor_thread, NULL);
	clean_up(&data);
	return (SUCCESS);
}
