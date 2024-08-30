/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:21:20 by csouita           #+#    #+#             */
/*   Updated: 2024/08/30 15:22:08 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_join_threads(t_data *data)
{
	int			i;
	pthread_t	monitorr;

	i = 0;
	data->start = get_time_of_day();
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philo_threads[i], NULL, routine, &data->philo[i]);
		i++;
	}
	pthread_create(&monitorr, NULL, monitor, data);
	pthread_join(monitorr, NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philo_threads[i], NULL);
		i++;
	}
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->data->is_dead);
		if (philo->data->is_dead_flag)
		{
			pthread_mutex_unlock(&philo->data->is_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->is_dead);
		if (is_eating(philo))
			return (NULL);
		if (is_sleeping(philo) == 0)
			break ;
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data *(data);
	data = (t_data *)arg;
	while (1)
	{
		if (data->num_of_meals > 0 && finished_meals(data->philo->data))
		{
			pthread_mutex_lock(&data->is_dead);
			data->is_dead_flag = 1;
			pthread_mutex_unlock(&data->is_dead);
			return (NULL);
		}
		pthread_mutex_lock(&data->last_meal);
		if (get_time_of_day()
			- data->philo->time_of_last_meal > data->time_to_die)
		{
			message("is dead", data->philo);
			pthread_mutex_lock(&data->is_dead);
			data->is_dead_flag = 1;
			pthread_mutex_unlock(&data->is_dead);
			pthread_mutex_unlock(&data->last_meal);
			return (NULL);
		}
		pthread_mutex_unlock(&data->last_meal);
	}
	return (NULL);
}

int	is_eating(t_philo *philo)
{
	if (philo->data->num_of_philos == 1)
	{
		message("has taking a fork", philo);
		return (one_philo(philo), 1);
	}
	pthread_mutex_lock(&philo->data->is_dead);
	if (philo->data->is_dead_flag)
		return (pthread_mutex_unlock(&philo->data->is_dead), 0);
	pthread_mutex_unlock(&philo->data->is_dead);
	pthread_mutex_lock(philo->left_fork);
	message("has taken a fork", philo);
	pthread_mutex_lock(philo->right_fork);
	message("has taken a fork", philo);
	message("is eating", philo);
	ft_sleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->last_meal);
	philo->time_of_last_meal = get_time_of_day();
	pthread_mutex_unlock(&philo->data->last_meal);
	pthread_mutex_lock(&philo->data->ate);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->ate);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->is_dead);
	if (philo->data->is_dead_flag)
	{
		pthread_mutex_unlock(&philo->data->is_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->is_dead);
	message("is sleeping", philo);
	ft_sleep(philo->data, philo->data->time_to_sleep);
	pthread_mutex_lock(&philo->data->is_dead);
	if (philo->data->is_dead_flag)
	{
		pthread_mutex_unlock(&philo->data->is_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->is_dead);
	message("is thinking", philo);
	usleep(100);
	return (1);
}
