/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:23:13 by maheraul          #+#    #+#             */
/*   Updated: 2023/05/19 22:43:17 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define MAXCALLOC 18446744073709551615UL

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					nb_philo;
	long int			time_start;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	int					dead;
	int					philo_full;
	long				eating;

	t_philo				*philo;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		print;
	pthread_mutex_t		full;
}						t_data;

typedef struct s_philo
{
	int					id;
	int					count_eat;
	long int			last_eat;
	pthread_t			tid;
	pthread_mutex_t		fork_left;
	pthread_mutex_t		*fork_right;
	pthread_mutex_t		eating;
	pthread_mutex_t		lock;

	t_data				*data;
}						t_philo;

//parsing.c
long long int			ft_atoi_limits(const char *str);
int						ft_long_limits(char *str);
int						ft_parse(int argc, char **argv);
//main
void					init_struct(t_data *data, int argc, char **argv);
//philo.c
void					create_thread(t_data *data, t_philo *philo);
void					*ft_ritual(void *ptr);
int						start_philo(t_data *data);
//action
int						is_alive(t_philo *philo, t_data *data);
int						take_fork(t_philo *philo, t_data *data);
int						eat(t_philo *philo, t_data *data);
void					sleep_think(t_philo *philo, t_data *data);
//utils.c
void					print_struct(int nb, t_philo *philo);
int						ft_strlen(const char *str);
void					ft_usleep(t_data *data, long ms);
int						print(int x, char *str, t_data *data);
long int				get_time(void);
//ft_calloc.c
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);

/*

si nombre philo est PAIR
	si time to eat + time to sleep + 10 >= time to die ILS VIVENT
	sinon ils meurent

si nombre philo est IMPAIR
	si (time to eat * 2)  + time to sleep + 10 >= time to die ILS VIVENT
	sinon ils meurent


*/

#endif