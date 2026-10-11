/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <saamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:39:53 by saamouss          #+#    #+#             */
/*   Updated: 2025/04/17 14:31:33 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			free_all(data);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitoring, data) != 0)
		free_all(data);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			free_all(data);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		free_all(data);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_loks);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->check_meals);
	free(data->forks);
	free(data->philos);
}

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			free_all(data);
		i++;
	}
	if (pthread_mutex_init(&data->check_meals, NULL) != 0)
		free_all(data);
	if (pthread_mutex_init(&data->print_loks, NULL) != 0)
		free_all(data);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		free_all(data);
}

void	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->num_philos)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->data = data;
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->num_philos];
		philo->last_meal_time = data->start_time;
		i++;
	}
}

int	philo_routine1(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		usleep(1000);
	}
	return (1);
}
