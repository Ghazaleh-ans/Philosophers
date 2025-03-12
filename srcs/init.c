#include "../includes/philo.h"

int		failed_malloc(void)
{
	ft_putstr_fd("Error: Memory allocation failed\n", 2);
	return (false);
}

bool	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_limit = -1;
	if (argc == 6)
		data->meals_limit = ft_atoi(argv[5]);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		failed_malloc();
	data->forks = malloc(sizeof(t_fork) * data->num_philos);
	if (!data->forks)
		failed_malloc();
	data->threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->threads)
		failed_malloc();
	data->simulation_running = true;
	data->start_time = get_time_in_ms();
	return (true);
}

bool	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->sim_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (false);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].mutex);
			pthread_mutex_destroy(&data->print_mutex);
			pthread_mutex_destroy(&data->sim_mutex);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].is_eating = false;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->philos[i].meal_mutex);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->threads[i], NULL, philo_routine, &data->philos[i]) != 0)
		{
			data->simulation_running = false;
			while (--i >= 0)
				pthread_join(data->threads[i], NULL);
			return (false);
		}
		precise_sleep(1);
		i++;
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
	{
		data->simulation_running = false;
		i = 0;
		while (i < data->num_philos)
			pthread_join(data->threads[i++], NULL);
		return (false);
	}
	i = 0;
	while (i < data->num_philos)
		pthread_detach(data->threads[i++]);
	return (true);
}
