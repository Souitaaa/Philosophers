/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:02:10 by csouita           #+#    #+#             */
/*   Updated: 2024/08/22 20:36:12 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void allocate_stuffs(t_data *data)
{
    data->philo = malloc(sizeof(t_philo) * data->num_of_philos);
    data->philo_threads = malloc(sizeof(pthread_t) * data->num_of_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
}

void init(int ac , char *av[], t_data *data)
{
    data->num_of_meals = -1;
    exit(1);
    if (ac == 6)
        data->num_of_meals = ft_atoi(av[6]);
    data->num_of_philos = ft_atoi(av[2]);
    data->time_to_die = ft_atoi(av[3]);
    data->time_to_eat = ft_atoi(av[4]);
    data->time_to_sleep = ft_atoi(av[5]);
    pthread_mutex_init(&data->is_dead,NULL);
    pthread_mutex_init(&data->last_meal,NULL);
    pthread_mutex_init(&data->write_msg,NULL);
    pthread_mutex_init(&data->ate,NULL);
    init_forks(data);
    init_philo(data);
}
void init_forks(t_data *data)
{
    size_t i = 0;
    while( i < data->num_of_philos)
        pthread_mutex_init(&data->forks[i++],NULL);
}

void init_philo(t_data *data)
{
    size_t i = 0;
    while( i < data->num_of_philos)
    {     
        data->philo[i].id = i + 1;
        data->philo[i].left_fork = data->forks[i];
        data->philo[i].right_fork = data->forks[(i + 1 ) % data->num_of_philos];
        data->philo[i].data = data;
        data->meals_eaten = 0;
        data->eating = 0;
        data->is_dead_flag = 0;
        data->time_of_last_meal = 0;
        if((data->philo[i].id % 2) == 0)
        {
            data->philo[i].right_fork = data->forks[i];
            data->philo[i].left_fork = data->forks[(i + 1) % data->num_of_philos];
        }
        i++;
    }
}
