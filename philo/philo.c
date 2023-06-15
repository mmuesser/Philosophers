/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:22:37 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/15 17:48:58 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

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
	data->mutex_fork = set_mutex_fork(ft_atoi(av[1]));
	if (!data->mutex_fork)
		return (NULL);
	data->philo = set_philo(ac, av, data);
	if (!data->philo)
		return (NULL);
	return (data);
}

int	check_nb_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if ((data->philo[i].nb_eat < data->philo[i].nb_must_eat)
			|| data->philo[i].nb_must_eat == -1)
			return (0);
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
			if (time_passed(data->time) - data->philo[i].time_last_meal
				>= data->philo[i].time_to_die)
			{
				pthread_mutex_lock(&data->mutex_dead);
				data->dead = 1;
				print(&data->philo[i], 4);
				pthread_mutex_unlock(&data->mutex_dead);
				usleep(((time_passed(data->time)
							- data->philo[i].time_last_meal)
						- data->philo[i].time_to_die) * 1000);
				return ;
			}
		}
		if (check_nb_eat(data) == 1)
		{
			data->dead = 1;
			return ;
		}
		usleep(50);
	}
}

/*A clean*/

int	main(int ac, char **av)
{
	struct timeval	time;
	t_data			*data;
	int				i;

	if (parsing(ac, av) == 1)
		return (1);
	data = set_data(ac, av);
	i = 0;
	gettimeofday(&time, NULL);
	data->time = time.tv_sec * 1000 + time.tv_usec / 1000;
	/*faire cas pour 1 philo*/
	while (i < ft_atoi(av[1]))
	{
		data->philo->time = data->time;
		if (pthread_create(&data->philo[i].thread,
				NULL, ma_routine, &data->philo[i]) != 0)
		{
			printf("Error creation thread\n");
			return (1);
		}
		i++;
	}
	check_dead(data);
	wait_thread(data, ft_atoi(av[1]));
	free(data->philo);
	free(data->mutex_fork);
	free(data);
	return (0);
}
