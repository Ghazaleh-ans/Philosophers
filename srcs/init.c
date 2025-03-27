/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:12 by gansari           #+#    #+#             */
/*   Updated: 2025/03/18 11:16:14 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_limit = -1;
	if (argc == 6)
		data->meals_limit = ft_atoi(argv[5]);
	data->simulation_running = true;
	data->start_time = get_time_in_ms();
	return ;
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
		if (data->num_philos == 1)
			data->philos[i].right_fork = &data->forks[i];
		else
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

bool	thread_error(t_data *data)
{
	data->simulation_running = false;
	join_threads(data, data->num_philos);
	return (false);
}

bool	init_threads(t_data *data)
{
	if (!create_threads(data))
		return (thread_error(data));
	if (pthread_create(&data->monitor_thread, NULL, monitor_routine, data) != 0)
		return (thread_error(data));
	return (true);
}
