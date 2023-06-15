/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:32:40 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/15 17:00:47 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	print(t_philo *philo, int i)
{
	pthread_mutex_lock(philo->mutex_printf);
	if (i == 0)
		printf ("[%lld] %d has taken a fork\n", \
		time_passed(philo->time), philo->num_philo);
	else if (i == 1)
		printf("[%lld] %d is eating\n", \
		time_passed(philo->time), philo->num_philo);
	else if (i == 2)
		printf("[%lld] %d is sleeping\n", \
		time_passed(philo->time), philo->num_philo);
	else if (i == 3)
		printf("[%lld] %d is thinking\n", \
		time_passed(philo->time), philo->num_philo);
	else if (i == 4)
		printf("[%lld] %d is died\n", \
		time_passed(philo->time), philo->num_philo);
	pthread_mutex_unlock(philo->mutex_printf);
}

void	wait_thread(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

long long	time_passed(long long time)
{
	struct timeval	now;
	long long		i;

	gettimeofday(&now, NULL);
	i = (now.tv_sec * 1000 + now.tv_usec / 1000) - time;
	return (i);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nb;
	int	signe;

	i = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * signe);
}
