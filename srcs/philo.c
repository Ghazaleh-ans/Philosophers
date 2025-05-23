/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:36 by gansari           #+#    #+#             */
/*   Updated: 2025/03/28 17:18:59 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (is_simulation_running(philo->data))
	{
		philo_eat(philo);
		if (!is_simulation_running(philo->data))
			break ;
		philo_sleep(philo);
		if (!is_simulation_running(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

void	philo_sleep(t_philo *philo)
{
	long long	start_sleeping_time;

	print_status(philo, "is sleeping");
	start_sleeping_time = get_time_in_ms();
	while (get_time_in_ms() - start_sleeping_time < philo->data->time_to_sleep
		&& is_simulation_running(philo->data))
		usleep(500);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep(500);
}
