/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:22:52 by gansari           #+#    #+#             */
/*   Updated: 2025/03/18 11:22:54 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->threads[i], NULL,
				philo_routine, &data->philos[i]) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	join_threads(t_data *data, int count)
{
	int	i;

	i = count;
	while (--i >= 0)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			exit_with_error("Error: Failed to join thread\n", 2);
	}
}
