/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:27:21 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/16 10:58:49 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*si philo pas proche de mourir -> think, sinon -> eat*/

#include "include/philo.h"

int	check_death(t_philo *philo)
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

int	eating(t_philo **philo)
{
	pthread_mutex_lock((*philo)->mutex_fork_left);
	if (check_death(*philo) == 1)
	{
		pthread_mutex_unlock((*philo)->mutex_fork_left);
		return (1);
	}
	print((*philo), 0);
	pthread_mutex_lock((*philo)->mutex_fork_right);
	if (check_death(*philo) == 1)
	{
		pthread_mutex_unlock((*philo)->mutex_fork_left);
		pthread_mutex_unlock((*philo)->mutex_fork_right);
		return (1);
	}
	print((*philo), 0);
	(*philo)->time_last_meal = time_passed((*philo)->time);
	(*philo)->nb_eat += 1;
	if (check_death(*philo) == 1)
	{
		pthread_mutex_unlock((*philo)->mutex_fork_left);
		pthread_mutex_unlock((*philo)->mutex_fork_right);
		return (1);
	}
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
	if (check_death(philo) == 1)
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
	if (check_death(philo) == 1)
		return (1);
	print(philo, 3);
	usleep(((philo->time_to_die - (philo->time_to_eat \
	+ philo->time_to_sleep)) / 2) * 1000);
	return (0);
}

void	*ma_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->num_philo % 2 == 0)
		usleep(500);
	while (1 && philo->nb_must_eat != 0)
	{
		if (eating(&philo) == 1)
			break ;
		if (sleeping(philo) == 1)
			break ;
		if (thinking(philo) == 1)
			break ;
	}
	printf("----- philo [%d] sort de la routine -----\n", philo->num_philo);
	return (NULL);
}

void	*routine_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(philo->mutex_fork_left);
	print(philo, 0);
	usleep(philo->time_to_die * 1000);
	return (NULL);
}
