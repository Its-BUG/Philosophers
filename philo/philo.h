/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <saamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:40:18 by saamouss          #+#    #+#             */
/*   Updated: 2025/04/22 13:23:56 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	long			start_time;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_loks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	check_meals;
	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	int				has_locked_left;
	int				has_locked_right;
}					t_philo;
int					is_death(t_philo *philo);
void				ft_usleep(size_t mls);
int					philo_routine1(t_philo *philo);
int					helper2(t_philo *philo);
int					helper(t_data *data, int full_philos);
int					check_eating(t_data *data, int full_philos);
int					check_args(char **argv);
int					ft_atoi(const char *str);
int					take_fork(t_philo *philo);
int					put_forks(t_philo *philo);
void				*philo_routine(void *arg);
int					eat(t_philo *philo);
int					sleep_think(t_philo *philo);
void				print_status(t_philo *philo, char *msg);
int					parse_args(t_data *data, int argc, char **argv);
long				get_time_in_ms(void);
void				*monitoring(void *arg);
void				init_philos(t_data *data);
void				init_mutexes(t_data *data);
void				start_threads(t_data *data);
void				free_all(t_data *data);
void				ft_precise_sleep(long duration, t_data *data);

#endif