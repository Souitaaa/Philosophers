/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:34:40 by csouita           #+#    #+#             */
/*   Updated: 2024/08/20 16:53:30 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define  PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>


typedef struct s_philo
{
    int id ;
    pthread_mutex_t right_fork;
    pthread_mutex_t left_fork;
    int meals_eaten;        
    struct s_data *data; 

}t_philo;


typedef struct s_data
{
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t time_to_die;
    size_t num_of_philos;
    size_t num_of_meals; 
    struct s_philo *philo;  
    pthread_mutex_t *forks;
    pthread_mutex_t write_msg;
    pthread_mutex_t last_meal;
    pthread_mutex_t is_dead;
    pthread_mutex_t ate;
    pthread_t *philo_threads;
}t_data;

// void *print_message_function( void *ptr );
void	ft_putstr_fd(char *s, int fd);
long	ft_atoi(char *str);
size_t	ft_strlen(char *s);
void init(int ac , char *av[], t_data *data);
size_t get_time_of_day();

#endif 