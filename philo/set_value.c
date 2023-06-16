/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:11:01 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/16 14:44:44 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

t_philo	*set_value_philo(t_philo *philo, int ac, char **av)
{
	int		i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].num_philo = i + 1;
		philo[i].time_last_eat = 0;
		philo[i].nb_eat = 0;
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo[i].nb_must_eat = ft_atoi(av[5]);
		else
			philo[i].nb_must_eat = -1;
		pthread_mutex_init(&philo[i].mutex_time_last_eat, NULL);
		pthread_mutex_init(&philo[i].mutex_nb_eat, NULL);
		i++;
	}
	return (philo);
}

t_philo	*copy_data(t_philo *philo, char **av, t_data *data)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].dead = &data->dead;
		philo[i].time = data->time;
		philo[i].mutex_printf = &data->mutex_printf;
		philo[i].mutex_dead = &data->mutex_dead;
		philo[i].mutex_fork_right = &data->mutex_fork[i];
		if (i == 0)
			philo[i].mutex_fork_left = &data->mutex_fork[ft_atoi(av[1]) - 1];
		else
			philo[i].mutex_fork_left = &data->mutex_fork[i - 1];
		i++;
	}
	return (philo);
}

t_philo	*set_philo(int ac, char **av, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
	{
		printf("Error create philo\n");
		return (NULL);
	}
	philo = set_value_philo(philo, ac, av);
	philo = copy_data(philo, av, data);
	return (philo);
}

pthread_mutex_t	*set_mutex_fork(int nb)
{
	pthread_mutex_t	*mutex_fork;
	int				i;

	mutex_fork = malloc(sizeof(pthread_mutex_t) * nb);
	if (!mutex_fork)
	{
		printf("Error create mutex_fork\n");
		return (NULL);
	}
	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&mutex_fork[i], NULL);
		i++;
	}
	return (mutex_fork);
}

t_data	*set_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->dead = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time = time_passed(0);
	pthread_mutex_init(&data->mutex_printf, NULL);
	pthread_mutex_init(&data->mutex_dead, NULL);
	data->mutex_fork = set_mutex_fork(data->nb_philo);
	if (!data->mutex_fork)
		return (NULL);
	data->philo = set_philo(ac, av, data);
	if (!data->philo)
		return (NULL);
	return (data);
}
