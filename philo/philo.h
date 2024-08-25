/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:34:40 by csouita           #+#    #+#             */
/*   Updated: 2024/08/25 18:58:29 by csouita          ###   ########.fr       */
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
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;      
    struct s_data *data; 
    int time_of_last_meal;
    // pthread_t monitor;
}t_philo;


typedef struct s_data
{
    long time_to_eat;
    long time_to_sleep;
    long time_to_die;
    long num_of_philos;
    long num_of_meals; 
    struct s_philo *philo;  
    pthread_mutex_t *forks;
    pthread_mutex_t write_msg;
    pthread_mutex_t last_meal;
    pthread_mutex_t is_dead;
    pthread_mutex_t ate;
    pthread_t *philo_threads;
    int is_dead_flag;
    int eating;
    size_t start;
    int meals_eaten;  
}t_data;

// void *print_message_function( void *ptr );
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *b, int c, size_t len);
long	ft_atoi(char *str);
size_t	ft_strlen(char *s);
void init(int ac , char *av[], t_data *data);
long get_time_of_day();
void is_eating(t_philo *philo);
void message(char *str ,t_philo *data);
void ft_sleep(t_data *data , long time);
void init_philo(t_data *data);
void init_forks(t_data *data);
void init(int ac , char *av[], t_data *data);
int allocate_stuffs(t_data *data);

#endif 