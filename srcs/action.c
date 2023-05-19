/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:18:21 by maheraul          #+#    #+#             */
/*   Updated: 2023/05/19 22:36:29 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_alive(t_philo *philo, t_data *data)
{
	int	dead;

	(void)philo;
	pthread_mutex_lock(&data->mutex_dead);
	dead = data->dead;
	pthread_mutex_unlock(&data->mutex_dead);
	return (dead);
}

int	take_fork(t_philo *philo, t_data *data)
{
	if (philo->id % 2)
	{
		if (&philo->fork_left == philo->fork_right)
		{
			print(philo->id, "has taken a fork\n", data);
			return (1);
		}
		pthread_mutex_lock(&philo->fork_left);
		print(philo->id, "has taken a fork\n", data);
		pthread_mutex_lock(philo->fork_right);
		print(philo->id, "has taken a fork\n", data);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		print(philo->id, "has taken a fork\n", data);
		pthread_mutex_lock(&philo->fork_left);
		print(philo->id, "has taken a fork\n", data);
	}
	return (0);
}

int	eat(t_philo *philo, t_data *data)
{
	print(philo->id, "is eating\n", data);
	pthread_mutex_lock(&philo->eating);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->eating);
	ft_usleep(data, data->time_eat);
	philo->count_eat++;
	if (philo->count_eat == data->must_eat)
	{
		pthread_mutex_lock(&data->full);
		data->philo_full++;
		pthread_mutex_unlock(&data->full);
		pthread_mutex_unlock(&philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	pthread_mutex_unlock(&philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

void	sleep_think(t_philo *philo, t_data *data)
{
	print(philo->id, "is sleeping\n", data);
	ft_usleep(data, data->time_sleep);
	print(philo->id, "is thinking\n", data);
}
