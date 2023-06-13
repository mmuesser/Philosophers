/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:22:37 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/13 11:57:29 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*idee routine :
	boucler pour checker l'etat du philo
	si son action est finie, voir si une action spe vient derriere
	si oui la faire si possible
	si non checker diff entre time_to_die et time_die
	si diff inf a time_to_eat et que fork droite et gauche dispo : manger
	
	
	differents cas possible :
		2 fourchettes dispo et diff time_to_die time_die inf time_to_eat -> manger/next
		2 fourchettes dispo et diff time_to_die time_die supp time_to_eat -> next/manger
		1 fourchette pas dispo et diff time_to_die time_die inf time_to_eat -> ??
		1 fourchette pas dispo et diff time_to_die time_die supp time_to_eat -> next
		2 fourchettes pas dispo et diff time_to_die time_die inf time_to_eat -> ??
		2 fourchettes pas dispo et diff time_to_die time_die supp time_to_eat -> next
		*/

#include "include/philo.h"

t_philo	*set_ptr(char **av)
{
	t_philo	*ptr;
	int		i;

	ptr = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!ptr)
	{
		printf("Error create ptr\n");
		return (NULL);
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		ptr[i].time_die = 0;
		ptr[i].time_eat = 0;
		ptr[i].time_sleep = 0;
		ptr[i].nb_eat = 0;
		ptr[i].nb_fork = 0;
		i++;
	}
	return (ptr);
}
pthread_mutex_t	*set_fork(char **av)
{
	pthread_mutex_t	*fork;
	int	i;

	fork = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!fork)
	{
		printf("Error create fork\n");
		return (NULL);
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

t_data	*set_data(int ac, char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = ft_atoi(av[5]);
	else
		data->nb_must_eat = -1;
	data->ptr = set_ptr(av);
	if (!data->ptr)
		return (NULL);
	data->fork = set_fork(av);
	return (data);
}

void	*ma_routine(void *data)
{
	int *i;

	while (data->nb_must_eat == -1 || (data->nb_must_eat != -1 && check_nb_eat() == 1))
	{
		
	}
	pthread_exit(EXIT_SUCCESS);
}
void	wait_thread(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_join(data->ptr[i].thread, NULL);
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
		if (pthread_create(&data->ptr[i].thread, NULL, ma_routine, data) != 0)
		{
			printf("Error creation thread\n");
			return (1);
		}
		i++;
	}
	wait_thread(data, ft_atoi(av[1]));
	free(data->ptr);
	free(data->fork);
	free(data);
	return (0);
}
