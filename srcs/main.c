/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 00:07:03 by maheraul          #+#    #+#             */
/*   Updated: 2023/05/19 17:43:05 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_struct(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi_limits(argv[1]);
	data->time_die = ft_atoi_limits(argv[2]);
	data->time_eat = ft_atoi_limits(argv[3]);
	data->time_sleep = ft_atoi_limits(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi_limits(argv[5]);
	else
		data->must_eat = -1;
	data->philo_full = 0;
	data->time_start = get_time();
}

int	main(int argc, char **argv)
{
	static t_data	data = {0};

	if (argc != 6 && argc != 5)
		return (1);
	if (ft_parse(argc, argv))
		return (1);
	init_struct(&data, argc, argv);
	start_philo(&data);
	return (0);
}
