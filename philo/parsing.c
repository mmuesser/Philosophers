/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:28:41 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/13 09:35:00 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	error(int c)
{
	if (c == 1)
		printf("Error nb_of_philo\n");
	if (c == 2)
		printf("Error time_to_die\n");
	if (c == 3)
		printf("Error time_to_eat\n");
	if (c == 4)
		printf("Error time_to_sleep\n");
	if (c == 5)
		printf("Error nb_of_times_each_philo_must_eat\n");		
	return (1);
}

int	nb_of_arg(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error\nNot enough/to many arguments\n");
		return (1);
	}
	return (0);
}

int	check_nb(char *av)
{
	int	nb;
	int	i;

	if (av[0] == '-')
		return (1);
	nb = atoi(av);
	i = ft_strlen(av) - 1;
	while (i >= 0)
	{
		if ((av[i] - 48) != (nb % 10))
			return (1);
		nb /= 10;
		i--;
	}
	return (0);
}

int	parsing(int ac, char **av)
{
	if (nb_of_arg(ac) == 1)
		return (1);
	if (check_nb(av[1]) == 1)
		return (error(1));
	if (check_nb(av[2]) == 1)
		return (error(2));
	if (check_nb(av[3]) == 1)
		return (error(3));
	if (check_nb(av[4]) == 1)
		return (error(4));
	if (ac == 6 && check_nb(av[5]) == 1)
		return (error(5));
	return (0);
}
