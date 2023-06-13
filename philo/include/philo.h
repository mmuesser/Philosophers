/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:37:48 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/13 11:01:22 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

/*pour fourchette, liste chainee 
avec alternance fourchette/philo*/

typedef struct s_philo
{
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			nb_eat;
	int			nb_fork;
	pthread_t	thread;
} t_philo;

typedef struct	s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	t_philo 		*ptr;
	pthread_mutex_t	*fork;
}	t_data;


int	nb_of_arg(int ac);
int	parsing(int ac, char **av);

int	ft_strlen(char *str);
int	ft_atoi(char *str);

#endif
