#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (is_simulation_running(philo->data))
	{
		timestamp = time_since_start(philo->data);
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	clean_up(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->num_philos)
			pthread_mutex_destroy(&data->philos[i++].meal_mutex);
		free(data->philos);
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i++].mutex);
		free(data->forks);
	}
	if (data->threads)
		free(data->threads);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->sim_mutex);
}

bool	is_simulation_running(t_data *data)
{
	bool	running;

	pthread_mutex_lock(&data->sim_mutex);
	running = data->simulation_running;
	pthread_mutex_unlock(&data->sim_mutex);
	return (running);
}
