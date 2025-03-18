/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:16:49 by gansari           #+#    #+#             */
/*   Updated: 2025/03/18 11:16:54 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long long ms)
{
	long long	start;
	long long	elapsed;
	long long	remaining;

	start = get_time_in_ms();
	while (1)
	{
		elapsed = get_time_in_ms() - start;
		if (elapsed >= ms)
			break ;
		remaining = ms - elapsed;
		if (remaining > 1)
		{
			if (remaining > 10)
				usleep(500);
			else
				usleep(100);
		}
	}
}

long long	time_since_start(t_data *data)
{
	return (get_time_in_ms() - data->start_time);
}
