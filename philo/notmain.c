/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:39:05 by csouita           #+#    #+#             */
/*   Updated: 2024/08/30 20:49:40 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->is_dead);
		if (philo->data->is_dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->data->is_dead);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->is_dead);
	}
	return (0);
}

int	finished_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->num_of_meals > 0)
		{
			pthread_mutex_lock(&data->ate);
			if (data->num_of_meals > data->philo[i].meals_eaten)
			{
				pthread_mutex_unlock(&data->ate);
				return (0);
			}
			pthread_mutex_unlock(&data->ate);
		}
		i++;
	}
	return (1);
}

void	message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->is_dead);
	if (philo->data->is_dead_flag)
	{
		pthread_mutex_unlock(&philo->data->write_msg);
		pthread_mutex_unlock(&philo->data->is_dead);
		return ;
	}
	printf("%ld %d %s\n", get_time_of_day() - philo->data->start, philo->id,
		str);
	pthread_mutex_unlock(&philo->data->write_msg);
	pthread_mutex_unlock(&philo->data->is_dead);
}

void	clean_up_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->write_msg);
	pthread_mutex_destroy(data->forks);
	pthread_mutex_destroy(&data->last_meal);
	pthread_mutex_destroy(&data->is_dead);
	pthread_mutex_destroy(&data->ate);
	free(data->forks);
	free(data->philo);
	free(data->philo_threads);
}

int	main(int ac, char *av[])
{
	t_data	data;
	int		i;
	long	num;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		write(2, "Error in arguments", 19);
		ft_putstr_fd("Error in arguments", 2);
		return (1);
	}
	while (ac > i)
	{
		num = ft_atoi(av[i]);
		if (num == 0)
		{
			write(2, "Error in arguments", 19);
			return (1);
		}
		i++;
	}
	init(ac, av, &data);
	create_join_threads(&data);
	clean_up_data(&data);
	return (0);
}
