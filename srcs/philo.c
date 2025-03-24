/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:36 by gansari           #+#    #+#             */
/*   Updated: 2025/03/18 11:16:41 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_sleep(10);
	while (is_simulation_running(philo->data))
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
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
		usleep(100);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (philo->data->num_philos % 2 != 0)
		usleep(500);
}
