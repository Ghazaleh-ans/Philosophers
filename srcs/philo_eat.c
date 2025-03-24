/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:31:40 by gansari           #+#    #+#             */
/*   Updated: 2025/03/18 11:31:43 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	even_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
}

void	odd_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_status(philo, "has taken a fork");
}

void	one_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_status(philo, "has taken a fork");
	precise_sleep(philo->data->time_to_die + 1);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	even_odd_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		even_philo_eat(philo);
	else
		odd_philo_eat(philo);
}

void	philo_eat(t_philo *philo)
{
	long long	start_eating_time;

	if (philo->data->num_philos == 1)
	{
		one_philo_eat(philo);
		return ;
	}
	even_odd_eat(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->is_eating = true;
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	start_eating_time = get_time_in_ms();
	while (get_time_in_ms() - start_eating_time < philo->data->time_to_eat
		&& is_simulation_running(philo->data))
		usleep(100);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}
