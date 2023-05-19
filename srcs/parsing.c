/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 02:43:53 by maheraul          #+#    #+#             */
/*   Updated: 2023/05/19 17:34:12 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long int	ft_atoi_limits(const char *str)
{
	long long int	i;
	long long int	total;

	i = 0;
	total = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		return ((long)INT_MAX + 1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || total > INT_MAX)
			return ((long)INT_MAX + 1);
		total = total * 10 + (str[i] - '0');
		i++;
	}
	return (total);
}

int	ft_long_limits(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (!(str[i] <= '9' && str[i] > '0') && str[i])
		i++;
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		i++;
		n++;
	}
	if (n > 10)
		return (1);
	return (0);
}

int	ft_parse(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!argv[i][0])
			return (write(2, "Error: Empty argument\n", 23));
		if (ft_atoi_limits(argv[i]) > INT_MAX || ft_long_limits(argv[i])
			|| ft_atoi_limits(argv[1]) == 0 || (argc == 6
				&& ft_atoi_limits(argv[5]) == 0))
			return (write(2, "Error: Wrong argument\n", 23));
	}
	return (0);
}
