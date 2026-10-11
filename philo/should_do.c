/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   should_do.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <saamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:40:01 by saamouss          #+#    #+#             */
/*   Updated: 2025/04/22 13:25:05 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	helper2(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo->has_locked_left = 1;
	if (is_death(philo))
		return (1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	philo->has_locked_right = 1;
	if (is_death(philo))
		return (1);
	print_status(philo, "has taken a fork");
	return (0);
}

int	take_forks(t_philo *philo)
{
	philo->has_locked_left = 0;
	philo->has_locked_right = 0;
	if (philo->id % 2 == 0)
	{
		if (is_death(philo))
			return (1);
		pthread_mutex_lock(philo->right_fork);
		philo->has_locked_right = 1;
		if (is_death(philo))
			return (1);
		print_status(philo, "has taken a fork");
		if (is_death(philo))
			return (1);
		pthread_mutex_lock(philo->left_fork);
		philo->has_locked_left = 1;
		if (is_death(philo))
			return (1);
		print_status(philo, "has taken a fork");
	}
	else
	{
		if (helper2(philo) == 1)
			return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (is_death(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->check_meals);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->check_meals);
	if (is_death(philo) == 1)
		return (1);
	print_status(philo, "is eating");
	ft_precise_sleep(philo->data->time_to_eat, philo->data);
	if (is_death(philo) == 1)
		return (1);
	return (0);
}

int	sleep_think(t_philo *philo)
{
	if (is_death(philo) == 1)
		return (1);
	print_status(philo, "is sleeping");
	ft_precise_sleep(philo->data->time_to_sleep, philo->data);
	if (is_death(philo) == 1)
		return (1);
	print_status(philo, "is thinking");
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1 && philo_routine1(philo) == 1)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (1)
	{
		if (is_death(philo) == 1)
			break ;
		if (take_forks(philo) == 1)
		{
			put_forks(philo);
			break ;
		}
		eat(philo);
		put_forks(philo);
		sleep_think(philo);
		usleep(1000);
	}
	return (NULL);
}
