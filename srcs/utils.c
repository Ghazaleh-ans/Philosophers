/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:17:01 by gansari           #+#    #+#             */
/*   Updated: 2025/03/18 11:17:03 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	failed_malloc(t_data *data, int status)
{
	if (status > 2 || status < 0)
	{
		ft_putstr_fd("Error: Wrong status code for failed malloc!\n", 2);
		return (false);
	}
	if (status == 1)
		free(data->philos);
	if (status == 2)
	{
		free(data->philos);
		free(data->forks);
	}
	ft_putstr_fd("Error: Memory allocation failed\n", 2);
	return (false);
}
