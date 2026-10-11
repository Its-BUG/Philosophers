/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <saamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:40:04 by saamouss          #+#    #+#             */
/*   Updated: 2025/04/20 23:59:29 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *msg)
{
	if (is_death(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->data->print_loks);
	printf("%ld %d %s\n", get_time_in_ms() - philo->data->start_time, philo->id,
		msg);
	pthread_mutex_unlock(&philo->data->print_loks);
}

int	check_eating(t_data *data, int full_philos)
{
	if (full_philos == data->num_philos)
	{
		pthread_mutex_lock(&data->dead_lock);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	return (0);
}

int	helper(t_data *data, int full_philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->check_meals);
		if (get_time_in_ms()
			- data->philos[i].last_meal_time > data->time_to_die)
		{
			print_status(&data->philos[i], "has died");
			pthread_mutex_lock(&data->dead_lock);
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_lock);
			pthread_mutex_unlock(&data->check_meals);
			return (-1);
		}
		if (data->must_eat > 0 && data->philos[i].meals_eaten >= data->must_eat)
			full_philos++;
		pthread_mutex_unlock(&data->check_meals);
		i++;
	}
	return (full_philos);
}

void	*monitoring(void *arg)
{
	int		full_philos;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		full_philos = 0;
		full_philos = helper(data, full_philos);
		if (full_philos == -1)
			return (NULL);
		if (check_eating(data, full_philos) == 1)
			return (NULL);
		usleep(1000);
	}
}
