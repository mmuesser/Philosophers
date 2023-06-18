/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 13:08:07 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/18 13:15:03 by mmuesser         ###   ########.fr       */
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

int	check_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_dead);
	if (*philo->dead != 0)
	{
		pthread_mutex_unlock(philo->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(philo->mutex_dead);
	return (0);
}

int	check_time_death(t_data *data, int i)
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
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].mutex_time_last_eat);
	return (0);
}

void	check_philo(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (check_time_death(data, i) == 1)
				return ;
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
