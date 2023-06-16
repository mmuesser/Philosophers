/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:22:37 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/16 14:42:15 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	check_nb_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philo[i].mutex_nb_eat);
		if ((data->philo[i].nb_eat < data->philo[i].nb_must_eat)
			|| data->philo[i].nb_must_eat == -1)
		{
			pthread_mutex_unlock(&data->philo[i].mutex_nb_eat);
			return (0);
		}
		pthread_mutex_unlock(&data->philo[i].mutex_nb_eat);
		i++;
	}
	return (1);
}

/*A clean*/

void	check_dead(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].mutex_time_last_eat);
			if (time_passed(data->time) - data->philo[i].time_last_eat
				>= data->philo[i].time_to_die)
			{
				pthread_mutex_unlock(&data->philo[i].mutex_time_last_eat);
				pthread_mutex_lock(&data->mutex_dead);
				data->dead = 1;
				print(&data->philo[i], 4);
				pthread_mutex_unlock(&data->mutex_dead);
				usleep(((time_passed(data->time)
							- data->philo[i].time_last_eat)
						- data->philo[i].time_to_die) * 1000);
				return ;
			}
			pthread_mutex_unlock(&data->philo[i].mutex_time_last_eat);
		}
		if (check_nb_eat(data) == 1)
		{
			pthread_mutex_lock(&data->mutex_dead);
			data->dead = 1;
			pthread_mutex_unlock(&data->mutex_dead);
			return ;
		}
		usleep(500);
	}
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
			printf("Error creation thread\n");
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
	check_dead(data);
	wait_thread(data, ft_atoi(av[1]));
	free_all(data);
	return (0);
}
