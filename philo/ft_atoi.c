/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <saamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:38:57 by saamouss          #+#    #+#             */
/*   Updated: 2025/04/22 13:18:31 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	r;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] != 0 && (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r')))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			s = s * -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (s * r);
}

void	ft_precise_sleep(long duration, t_data *data)
{
	long	start;

	start = get_time_in_ms();
	while (1)
	{
		if (is_death(data->philos) == 1)
			return ;
		pthread_mutex_lock(&data->dead_lock);
		if (data->dead || get_time_in_ms() - start >= duration)
		{
			pthread_mutex_unlock(&data->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&data->dead_lock);
		usleep(100);
	}
}

int	is_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

int	put_forks(t_philo *philo)
{
	if (philo->has_locked_left)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->has_locked_left = 0;
	}
	if (philo->has_locked_right)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->has_locked_right = 0;
	}
	if (is_death(philo) == 1)
		return (1);
	return (0);
}
