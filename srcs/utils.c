/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:00:08 by maheraul          #+#    #+#             */
/*   Updated: 2023/05/19 22:43:09 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time);
}

int	print(int x, char *str, t_data *data)
{
	long int	time;

	pthread_mutex_lock(&data->print);
	if (is_alive(data->philo, data))
	{
		pthread_mutex_unlock(&data->print);
		return (0);
	}
	time = get_time();
	time = time - data->time_start;
	printf("%08ld %d %s", time, x, str);
	pthread_mutex_unlock(&data->print);
	return (0);
}

void	ft_usleep(t_data *data, long ms)
{
	long	begin;

	begin = get_time();
	(void)data;
	while (get_time() - begin < ms)
	{
		pthread_mutex_lock(&data->mutex_dead);
		if (data->dead == 1)
		{
			pthread_mutex_unlock(&data->mutex_dead);
			return ;
		}
		pthread_mutex_unlock(&data->mutex_dead);
		usleep(10);
	}
}
