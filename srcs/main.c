/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:20 by gansari           #+#    #+#             */
/*   Updated: 2025/03/18 11:16:22 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: ./philo number_of_philosophers time_to_die ", 1);
		ft_putstr_fd("time_to_eat time_to_sleep ", 1);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 1);
		return (ERROR);
	}
	if (check_input(argc, argv) == 1)
		return (ERROR);
	if (!init_data(&data, argc, argv))
		return (exit_with_error("Error: Failed to initialize data\n", 2));
	if (!init_mutexes(&data) || !init_philos(&data) || !init_threads(&data))
	{
		clean_up(&data);
		return (ERROR);
	}
	if (pthread_join(data.monitor_thread, NULL) != 0)
		return (exit_with_error("Error: Failed to join monitor thread\n", 2));
	clean_up(&data);
	return (SUCCESS);
}