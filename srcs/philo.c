/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:22:09 by maheraul          #+#    #+#             */
/*   Updated: 2023/05/19 22:36:15 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_ritual(void *ptr)
{
	t_philo	*philo;
	t_data	*data;

	philo = ptr;
	data = philo->data;
	if (philo->id % 2)
	{
		ft_usleep(data, data->time_eat * 0.25);
	}
	while (!is_alive(philo, data))
	{
		if (data->nb_philo % 2 && philo->count_eat)
			ft_usleep(data, data->time_die * 0.2);
		if (take_fork(philo, data))
			break ;
		if (eat(philo, data))
			return (NULL);
		sleep_think(philo, data);
	}
	return (NULL);
}

int	check_finish(t_data *data, t_philo *philo, int i)
{
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].eating);
		data->eating = get_time() - philo[i].last_eat;
		pthread_mutex_unlock(&philo[i].eating);
		if (data->eating >= data->time_die)
		{
			pthread_mutex_lock(&data->mutex_dead);
			data->dead = 1;
			pthread_mutex_unlock(&data->mutex_dead);
			pthread_mutex_lock(&data->print);
			printf("%08ld %d died\n", get_time() - data->time_start, i + 1);
			pthread_mutex_unlock(&data->print);
			break ;
		}
		pthread_mutex_lock(&data->full);
		if (data->philo_full == data->nb_philo)
			return (pthread_mutex_unlock(&data->full), 0);
		pthread_mutex_unlock(&data->full);
		if (i == data->nb_philo - 1)
			i = -1;
		usleep(20);
	}
	return (0);
}

void	create_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->dead = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex_dead, NULL);
	pthread_mutex_init(&data->full, NULL);
	while (i < data->nb_philo)
	{
		philo[i].last_eat = data->time_start;
		pthread_create(&philo[i].tid, NULL, ft_ritual, &philo[i]);
		i++;
	}
	check_finish(data, philo, -1);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philo[i].tid, NULL);
		i++;
	}
	return ;
}

int	start_philo(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = ft_calloc(sizeof(t_philo), data->nb_philo);
	data->philo = philo;
	if (!philo)
		return (1);
	i = -1;
	while (++i < data->nb_philo - 1)
		philo[i].fork_right = &philo[i + 1].fork_left;
	philo[i].fork_right = &philo[0].fork_left;
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&philo[i].fork_left, NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].count_eat = 0;
		pthread_mutex_init(&philo[i].eating, NULL);
	}
	create_thread(data, philo);
	free(philo);
	return (0);
}
