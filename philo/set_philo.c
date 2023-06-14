/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:11:01 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/14 17:48:23 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

t_philo	*set_value_philo(t_philo *philo, int ac, char **av)
{
	int		i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (i == 0)
			*philo[i].dead = 0;
		else
			philo[i].dead = &philo[0].dead;
		philo[i].num_philo = i + 1;
		philo[i].time_die = 0;
		philo[i].nb_eat = 0;
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			data->nb_must_eat = ft_atoi(av[5]);
		else
			data->nb_must_eat = -1;
		pthread_mutex_init(&philo[i].mutex_dead);
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
		philo[i].time = &data->time;
		philo[i].mutex_fork_right = data->mutex_fork[i];
		if (i == 0)
			philo[i].mutex_fork_left = data->mutex_fork[ft_atoi(av[1]) - 1];
		else
			philo[i].mutex_fork_left = data->mutex_fork[i - 1];
		i++;
	}
	return (philo);
}

t_philo	*set_philo(int ac, char **av, t_data *data)
{
	t_philo	*philo;
	
	philo = mallloc(sizeof(philo) * ft_atoi(av[1]));
	if (!philo)
	{
		printf("Error create philo\n");
		return (NULL);
	}
	philo = set_value_philo(philo, ac, av);
	philo = copy_data(philo, av, data);
	return (philo);
}
