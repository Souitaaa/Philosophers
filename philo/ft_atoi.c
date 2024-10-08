/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csouita <csouita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:42:26 by csouita           #+#    #+#             */
/*   Updated: 2024/08/30 15:00:52 by csouita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	long (i), (sig), (res);
	res = 0;
	i = 0;
	sig = 1;
	while (str[i] == 32 && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sig = -1;
		if (str[i] == '-' || str[i] == '+')
			return (0);
	}
	while (str[i] == '0')
		i++;
	if ((ft_strlen(&str[i]) > 11))
		return (0);
	while (str[i] >= '0' && str[i] <= '9' && str[i])
		res = res * 10 + str[i++] - '0';
	if (res * sig < 0)
		return (0);
	if (str[i] || str[i - 1] == '-' || str[i - 1] == '+')
		return (0);
	return (sig * res);
}
