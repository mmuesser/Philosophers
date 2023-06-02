/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:22:37 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/02 17:10:49 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

t_philo	*set_ptr()
{
	t_philo	*ptr;
	int		i;

	ptr = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (!ptr)
	{
		printf("\n");
		return (NULL);
	}
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		ptr[i]->nb = i + 1;
		ptr[i]->time_to_die = 0;
		ptr[i]->time_to_eat = 0;
		ptr[i]->time_to_sleep = 0;
		ptr[i]->nb_eat = 0;
		i++;
	}
}

t_data	set_data(int ac, char **av)
{
	t_data data;

	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.nb_must_eat = ft_atoi(av[5]);
	else
		data.nb_must_eat = -1;
	data.ptr = set_ptr(av);
	if (!data.ptr)
		return (NULL);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av) == 1)
		return (1);
	data = set_data(av);
	return (0);
}
