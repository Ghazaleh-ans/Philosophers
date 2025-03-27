/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:29 by gansari           #+#    #+#             */
/*   Updated: 2025/03/18 11:16:31 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*death_news(t_data *data, int i)
{
	pthread_mutex_lock(&data->sim_mutex);
	data->simulation_running = false;
	pthread_mutex_unlock(&data->sim_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d died\n", time_since_start(data), data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
	return (NULL);
}

void	*enough_food_news(t_data *data)
{
	pthread_mutex_lock(&data->sim_mutex);
	data->simulation_running = false;
	pthread_mutex_unlock(&data->sim_mutex);
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (is_simulation_running(data))
	{
		i = 0;
		while (i < data->num_philos && is_simulation_running(data))
		{
			if (check_if_philo_died(&data->philos[i]))
				return (death_news(data, i));
			i++;
		}
		if (data->meals_limit > 0 && all_philos_ate_enough(data))
			return (enough_food_news(data));
		usleep(1000);
	}
	return (NULL);
}

bool	check_if_philo_died(t_philo *philo)
{
	long long	time_since_last_meal;
	bool		is_eating;

	pthread_mutex_lock(&philo->meal_mutex);
	time_since_last_meal = get_time_in_ms() - philo->last_meal_time;
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (!is_eating && time_since_last_meal > philo->data->time_to_die)
		return (true);
	return (false);
}

bool	all_philos_ate_enough(t_data *data)
{
	int		i;
	bool	all_ate_enough;
	int		meals_eaten;

	all_ate_enough = true;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		meals_eaten = data->philos[i].meals_eaten;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (meals_eaten < data->meals_limit)
		{
			all_ate_enough = false;
			break ;
		}
		i++;
	}
	return (all_ate_enough);
}
