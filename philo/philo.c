/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:39:05 by csouita           #+#    #+#             */
/*   Updated: 2024/08/20 16:11:44 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time_of_day()
{
    struct  timeval tv;
    size_t time;
    time = tv.tv_sec * 1000 + tv.tv_sec / 1000;
    return time;
}

int main(int ac, char *av[])
{
    t_data *data = NULL;
    int i = 1;
    long num ;
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
    init(ac,av,data);
    return 0;
}
