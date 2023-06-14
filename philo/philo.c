/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:22:37 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/14 11:11:24 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

t_philo	*set_philo(char **av)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!philo)
	{
		printf("Error create philo\n");
		return (NULL);
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].num_philo = i + 1;
		philo[i].time_die = 0;
		philo[i].time_eat = 0;
		philo[i].time_sleep = 0;
		philo[i].nb_eat = 0;
		philo[i].nb_fork = 0;
		i++;
	}
	return (philo);
}

pthread_mutex_t	*set_mutex_fork(char **av)
{
	pthread_mutex_t	*mutex_fork;
	int				i;

	mutex_fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!mutex_fork)
	{
		printf("Error create mutex_fork\n");
		return (NULL);
	}
	i = 0;
	while (i < ft_atoi(av[1]))
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
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = -1;
	data->philo = set_philo(av);
	if (!data->philo)
		return (NULL);
	data->mutex_fork = set_mutex_fork(av);
	return (data);
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

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	if (parsing(ac, av) == 1)
		return (1);
	data = set_data(ac, av);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (pthread_create(&data->philo[i].thread, NULL, ma_routine, data) != 0)
		{
			printf("Error creation thread\n");
			return (1);
		}
		i++;
	}
	wait_thread(data, ft_atoi(av[1]));
	free(data->philo);
	free(data->mutex_fork);
	free(data);
	return (0);
}
