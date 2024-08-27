/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:39:05 by csouita           #+#    #+#             */
/*   Updated: 2024/08/27 22:58:59 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_of_day()
{
    struct  timeval tv;
	gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


void ft_sleep(t_data *data , long time)
{
    long start ;
    start = get_time_of_day();
    while (get_time_of_day() - start < time)
    {
        pthread_mutex_lock(&data->is_dead);
        if(data->is_dead_flag)
        {
            pthread_mutex_unlock(&data->is_dead);
            break;
        }
        pthread_mutex_unlock(&data->is_dead);
        usleep(500);
    }
}

int is_sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->is_dead);
    if(philo->data->is_dead_flag)
    {
        pthread_mutex_unlock(&philo->data->is_dead);
        return 0;
    }
    pthread_mutex_unlock(&philo->data->is_dead);
    message("is sleeping",philo);
    ft_sleep(philo->data ,philo->data->time_to_sleep);
    pthread_mutex_lock(&philo->data->is_dead);
    if(philo->data->is_dead_flag)
    {
        pthread_mutex_unlock(&philo->data->is_dead);
        return 0;
    }   
    pthread_mutex_unlock(&philo->data->is_dead);
    message("is thinking",philo);
    usleep(500);
    
    return 1;
}

void *routine(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;
    if(philo->id % 2 == 0)
        usleep(200);  
    while(1)
    {
        pthread_mutex_lock(&philo->data->is_dead);
        if(philo->data->is_dead_flag)
        {
            pthread_mutex_unlock(&philo->data->is_dead);
            return NULL;
        }
        pthread_mutex_unlock(&philo->data->is_dead);
        
        // exit(1);
        is_eating(philo);
        if(is_sleeping(philo) == 0)
            break;
        usleep(500);
    }      
    return NULL;
}

void *monitor(void *arg)
{
    int i = 0;
    t_data *data = (t_data *)arg;

    while(1)    
    {
        if(data->num_of_meals > 0)
        {
            if(finished_meals(data->philo->data))
                return (data->is_dead_flag = 1, NULL);
        }
            
            pthread_mutex_lock(&data->last_meal);
            if(get_time_of_day() - data->philo[i].time_of_last_meal > data->time_to_die)
            {
                
                    
                
                pthread_mutex_lock(&data->is_dead); 
                data->is_dead_flag = 1;
                pthread_mutex_unlock(&data->is_dead);
                printf("%ld %d %s" ,get_time_of_day() - data->start,data->philo[i].id,"is dead\n");
               
                pthread_mutex_unlock(&data->last_meal);
                return NULL;
            }
            pthread_mutex_unlock(&data->last_meal);
           
    }
    return NULL;
    
}

int finished_meals(t_data *data)
{
    int  i = 0;
    while(i < data->num_of_philos)
    {
        if(data->num_of_meals > 0)
        {
            
            if(data->num_of_meals >  data->philo[i].meals_eaten)
            {
                return 0;
            }
            
        }
        i++;
    }
   
    
    return 1;
}




void message(char *str ,t_philo *philo)
{
    if (philo->data->is_dead_flag == 1)
        return ;
    pthread_mutex_lock(&philo->data->write_msg);
    pthread_mutex_lock(&philo->data->is_dead);
    if(philo->data->is_dead_flag)
    {
        // printf("is dead5\n");
        pthread_mutex_unlock(&philo->data->is_dead);
        return;
    }
    pthread_mutex_unlock(&philo->data->is_dead);
    printf("%ld %d %s\n", get_time_of_day() - philo->data->start ,philo->id,str);
    pthread_mutex_unlock(&philo->data->write_msg);
}

void create_join_threads(t_data *data)
{
    int i = 0;
    pthread_t monitorr ;
    data->start = get_time_of_day();
    while(i < data->num_of_philos)
    {
        pthread_create(&data->philo_threads[i],NULL,routine,&data->philo[i]);
        i++;
    }
    pthread_create(&monitorr,NULL,monitor,data);
    pthread_join(monitorr,NULL);
   
    i = 0;
    while(i < data->num_of_philos)
    {
        pthread_join(data->philo_threads[i],NULL);
        i++;
    }
}

void is_eating(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    printf("%ld %d %s\n", get_time_of_day() - philo->data->start ,philo->id, "has taken a fork");

    pthread_mutex_lock(philo->right_fork);
    printf("%ld %d %s\n", get_time_of_day() - philo->data->start ,philo->id, "has taken a fork");

    printf("%ld %d %s\n", get_time_of_day() - philo->data->start ,philo->id, "is eating");
    ft_sleep(philo->data,philo->data->time_to_eat);
    pthread_mutex_lock(&philo->data->last_meal);
    philo->time_of_last_meal = get_time_of_day();
    pthread_mutex_unlock(&philo->data->last_meal);


    
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

int main(int ac, char *av[])
{
    t_data data;
    int i = 1;
    long num ;
    ft_memset(&data, 0, sizeof(t_data));
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
