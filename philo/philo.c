/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:22:37 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/14 17:53:04 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

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
	data->time = 0;
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = -1;
	data->mutex_fork = set_mutex_fork(av);
	if (!data->mutex_fork)
		return (NULL);
	data->philo = set_philo(av, data);
	if (!data->philo)
		return (NULL);
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

/*creer nouveau thread pour checker et annoncer mort philo*/

int	main(int ac, char **av)
{
	struct timeval time;
	t_data	*data;
	int		i;

	if (parsing(ac, av) == 1)
		return (1);
	data = set_data(ac, av);
	i = 0;
	gettimeofday(&time, NULL);
	data->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	while (i < ft_atoi(av[1]))
	{
		data->philo->time = data->time;
		if (pthread_create(&data->philo[i].thread, NULL, ma_routine, &data->philo[i]) != 0)
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
