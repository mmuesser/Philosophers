/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:22:37 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/19 11:00:23 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*routine_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(philo->mutex_fork_left);
	if (check_is_dead(philo) == 1)
	{
		pthread_mutex_unlock(philo->mutex_fork_left);
		return (NULL);
	}
	print(philo, 0);
	usleep(philo->time_to_die * 1000);
	pthread_mutex_unlock(philo->mutex_fork_left);
	return (NULL);
}

int	one_philo(t_data *data)
{
	data->philo[0].time = data->time;
	if (pthread_create(&data->philo[0].thread,
			NULL, routine_one_philo, &data->philo[0]) != 0)
	{
		printf("Error creation thread\n");
		free_all(data);
		return (1);
	}
	return (0);
}

int	multiple_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		data->philo[i].time = data->time;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread,
				NULL, routine_multiple_philo, &data->philo[i]) != 0)
		{
			pthread_mutex_lock(&data->mutex_printf);
			printf("Error creation thread\n");
			pthread_mutex_unlock(&data->mutex_printf);
			free_all(data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	struct timeval	time;
	t_data			*data;

	if (parsing(ac, av) == 1)
		return (1);
	data = set_data(ac, av);
	gettimeofday(&time, NULL);
	data->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (ft_atoi(av[1]) == 1)
	{
		if (one_philo(data) == 1)
			return (1);
	}
	else
		if (multiple_philo(data) == 1)
			return (1);
	check_philo(data);
	wait_thread(data, ft_atoi(av[1]));
	free_all(data);
	return (0);
}
