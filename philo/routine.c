/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:27:21 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/14 18:01:36 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*si philo pas proche de mourir -> think, sinon -> eat*/

#include "include/philo.h"

int	check_death(t_philo *philo, int i)
{
	if (philo->dead == 1)
		return (1);
	if (i == 1)
	{
		if (time_passed(philo->time) - philo->time_die >= philo->time_to_die)
			return (1);
	}
	else if (i == 2)
	{
		if (time_passed(philo->time) - philo->time_to_sleep >= philo->time_to_die)
			return (1);
	}
	return (0);
}

t_philo	*eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork_left);
	if (check_death(philo, 1) == 1)
		return (NULL);
	printf()
	pthread_mutex_lock(&philo->mutex_fork_right);
	if (check_death(philo, 1) == 1)
		return (NULL);
	printf()
	philo->time_die = time_passed(philo->time);
	if (check_death(philo, 1) == 1)
		return (NULL);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex_fork_left);
	pthread_mutex_unlock(&philo->mutex_fork_right);
	return (philo);
}

t_philo	*sleep(t_philo *philo)
{
	if (check_death(philo, 2) == 1)
		return (NULL);
	usleep(philo->time_to_sleep * 1000);
	return (philo);
}

void	*ma_routine(void *philo)
{
	
	while (philo->nb_must_eat == -1
		|| (philo->nb_must_eat != -1 && check_nb_eat() == 1))
	{
		if (philo = eat(philo) == NULL)
			return (NULL);
		philo = sleep(philo);
	}
	pthread_exit(EXIT_SUCCESS);
}
