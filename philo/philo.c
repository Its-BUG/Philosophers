/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saamouss <saamouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:39:58 by saamouss          #+#    #+#             */
/*   Updated: 2025/04/14 22:20:37 by saamouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != 0)
	{
		j = 0;
		while (argv[i][j] != 0)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6 || check_args(argv) == 1 || ft_atoi(argv[1]) > 200)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->dead = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(&data, argc, argv) == 1)
		return (1);
	data.start_time = get_time_in_ms();
	data.forks = malloc(sizeof(pthread_mutex_t) * data.num_philos);
	data.philos = malloc(sizeof(t_philo) * data.num_philos);
	if (!data.forks || !data.philos)
		return (1);
	init_mutexes(&data);
	init_philos(&data);
	start_threads(&data);
	free_all(&data);
	return (0);
}
