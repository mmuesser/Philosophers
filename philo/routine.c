/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:27:21 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/18 13:39:07 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	lock_forks(t_philo *philo)
{
	if (philo->num_philo % 2 == 0)
	{
		pthread_mutex_lock(philo->mutex_fork_left);
		if (check_is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->mutex_fork_left);
			return (1);
		}
		print(philo, 0);
		pthread_mutex_lock(philo->mutex_fork_right);
	}
	else
	{
		pthread_mutex_lock(philo->mutex_fork_right);
		if (check_is_dead(philo) == 1)
		{
			pthread_mutex_unlock(philo->mutex_fork_right);
			return (1);
		}
		print(philo, 0);
		pthread_mutex_lock(philo->mutex_fork_left);
	}
	return (0);
}

int	eating(t_philo **philo)
{
	if (lock_forks(*philo) == 1)
		return (2);
	if (check_is_dead(*philo) == 1)
		return (1);
	print((*philo), 0);
	pthread_mutex_lock(&(*philo)->mutex_time_last_eat);
	(*philo)->time_last_eat = time_passed((*philo)->time);
	pthread_mutex_unlock(&(*philo)->mutex_time_last_eat);
	pthread_mutex_lock(&(*philo)->mutex_nb_eat);
	(*philo)->nb_eat += 1;
	pthread_mutex_unlock(&(*philo)->mutex_nb_eat);
	if (check_is_dead(*philo) == 1)
		return (1);
	print((*philo), 1);
	if ((*philo)->time_to_eat > (*philo)->time_to_die)
		usleep((*philo)->time_to_die * 1000);
	else
		usleep((*philo)->time_to_eat * 1000);
	pthread_mutex_unlock((*philo)->mutex_fork_left);
	pthread_mutex_unlock((*philo)->mutex_fork_right);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (check_is_dead(philo) == 1)
		return (1);
	print(philo, 2);
	if (philo->time_to_eat + philo->time_to_sleep > philo->time_to_die)
		usleep((philo->time_to_die - philo->time_to_eat) * 1000);
	else
		usleep(philo->time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (check_is_dead(philo) == 1)
		return (1);
	print(philo, 3);
	usleep(((philo->time_to_die - (philo->time_to_eat \
	+ philo->time_to_sleep)) / 2) * 1000);
	return (0);
}

void	*routine_multiple_philo(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *) arg;
	if (philo->num_philo % 2 == 0)
		thinking(philo);
	while (1 && philo->nb_must_eat != 0)
	{
		i = eating(&philo);
		if (i == 1)
		{
			pthread_mutex_unlock(philo->mutex_fork_left);
			pthread_mutex_unlock(philo->mutex_fork_right);
			break ;
		}
		else if (i == 2)
			break ;
		if (sleeping(philo) == 1)
			break ;
		if (thinking(philo) == 1)
			break ;
	}
	return (NULL);
}
