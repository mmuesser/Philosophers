/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:27:21 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/14 11:01:23 by mmuesser         ###   ########.fr       */
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
		1 fourchette dispo et diff time_to_die time_die inf time_to_eat -> ??
		1 fourchette dispo et diff time_to_die time_die supp time_to_eat -> next
		0 fourchettes dispo et diff time_to_die time_die inf time_to_eat -> ??
		0 fourchettes dispo et diff time_to_die time_die supp time_to_eat -> next
*/

#include "include/philo.h"

void	*ma_routine(void *data)
{
	int	i;

	i = 0;
	while (data->nb_must_eat == -1
		|| (data->nb_must_eat != -1 && check_nb_eat() == 1))
	{
		if (data->fork[])
		i++;
		if (i >= data->nb_philo)
			i = 0;
	}
	pthread_exit(EXIT_SUCCESS);
}
