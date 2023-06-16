/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:11:52 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/16 14:42:15 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	free_all(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->philo)
		{
			i = -1;
			while (++i < data->nb_philo)
			{
				pthread_mutex_destroy(&data->philo[i].mutex_nb_eat);
				pthread_mutex_destroy(&data->philo[i].mutex_time_last_eat);
			}
			free(data->philo);
		}
		if (data->mutex_fork)
		{
			i = -1;
			while (++i < data->nb_philo)
				pthread_mutex_destroy(&data->mutex_fork[i]);
			free(data->mutex_fork);
		}
		pthread_mutex_destroy(&data->mutex_printf);
		pthread_mutex_destroy(&data->mutex_dead);
		free(data);
	}
}
