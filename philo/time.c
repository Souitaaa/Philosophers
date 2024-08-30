/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:03:08 by csouita           #+#    #+#             */
/*   Updated: 2024/08/30 14:58:09 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_of_day(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(t_data *data, long time)
{
	long	start;

	start = get_time_of_day();
	while (get_time_of_day() - start < time)
	{
		pthread_mutex_lock(&data->is_dead);
		if (data->is_dead_flag)
		{
			pthread_mutex_unlock(&data->is_dead);
			break ;
		}
		pthread_mutex_unlock(&data->is_dead);
	}
}
