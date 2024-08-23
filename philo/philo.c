/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:39:05 by csouita           #+#    #+#             */
/*   Updated: 2024/08/23 20:13:17 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time_of_day()
{
    struct  timeval tv;
    size_t time;
	gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_sec / 1000;
    return time;
}
// #include <sys/time.h>
// #include <stddef.h>

// size_t get_time_of_day()
// {
//     struct timeval tv;
//     size_t time;

//     // Populate tv with the current time
//     gettimeofday(&tv, NULL);

//     // Convert the time to milliseconds
//     time = tv.tv_sec * 1000 + tv.tv_usec / 1000;

//     return time;
// }


void ft_sleep(t_data *data , size_t time)
{
    int start ;
    start = get_time_of_day();
    while (get_time_of_day() - start < time)
    {
        pthread_mutex_lock(&data->is_dead);
        if(data->is_dead_flag)
        {
            printf("is dead");
            break;
        }
        pthread_mutex_unlock(&data->is_dead);
        sleep(100);
    }
}

void is_sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->is_dead);
    if(philo->data->is_dead_flag)
    {
        printf("is_dead");
        return;
    }
    pthread_mutex_unlock(&philo->data->is_dead);
    if(philo->id % 2 == 0)
        usleep(200);
    message("is sleeping",philo);
    ft_sleep(philo->data ,philo->data->time_to_sleep);
    pthread_mutex_lock(&philo->data->is_dead);
    if(philo->data->is_dead_flag)
    {
        printf("is_dead");
        return;
    }   
    pthread_mutex_unlock(&philo->data->is_dead);
    message("is thinking",philo);
}

void *routine(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;
    if(philo->id % 2 == 0)
        usleep(200);  
    while(1)
    {        
        is_eating(philo);
        is_sleeping(philo);
        if(philo->data->num_of_philos < 20)
            usleep(500);
    }      
    return NULL;
}

void message(char *str ,t_philo *philo)
{
    pthread_mutex_lock(&philo->data->write_msg);
    pthread_mutex_lock(&philo->data->is_dead);
    if(philo->data->is_dead_flag)
    {
        printf("is dead 2");
        pthread_mutex_unlock(&philo->data->is_dead);
        return;
    }
    pthread_mutex_unlock(&philo->data->is_dead);
    printf(" %ld %d %s\n", get_time_of_day() - philo->data->start ,philo->id,str);
    pthread_mutex_unlock(&philo->data->write_msg);
}

void create_join_threads(t_data *data)
{
    size_t i = 0;
    
    while(i < data->num_of_philos)
    {
        pthread_create(&data->philo_threads[i],NULL,routine,&data->philo[i]);
        i++;
    }
    i = 0;
    while(i < data->num_of_philos)
    {
        pthread_join(data->philo_threads[i],NULL);
        i++;
    }
}

void is_eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork);
    message("has taken a fork",philo);
    pthread_mutex_lock(&philo->right_fork);
    message("has taken a fork",philo);
    message("is eating",philo);
    pthread_mutex_lock(&philo->data->ate);
    philo->data->eating++;
    pthread_mutex_unlock(&philo->data->ate);
    pthread_mutex_lock(&philo->data->last_meal);
    philo->data->time_of_last_meal = get_time_of_day();
    pthread_mutex_unlock(&philo->data->last_meal);
    philo->data->meals_eaten++;
    pthread_mutex_unlock(&philo->left_fork);
    pthread_mutex_unlock(&philo->right_fork);
}

int main(int ac, char *av[])
{
    t_data data;
    int i = 1;
    long num ;
    ft_memset(&data,0,sizeof(t_data));
    data.start = get_time_of_day();
    if (ac != 5 && ac != 6)
    {
        ft_putstr_fd("Error in arguments",2);
        return 1;
    } 
    while(ac > i)
    {
        num  = ft_atoi(av[i]);
        // printf("av == %s\n",av[i]);
        if (num == 0)
        {
            // printf("num ==== %ld\n",num);
            ft_putstr_fd("Error in arguments2",2);
            return 1;
        }
        i++;
    }
    // data.start = get_time_of_day();
    init(ac,av,&data);
    create_join_threads(&data);
    return 0;
}
