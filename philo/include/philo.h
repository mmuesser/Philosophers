/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:37:48 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/14 11:12:26 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

/*pour fourchette, liste chainee 
avec alternance fourchette/philo*/

typedef struct s_philo
{
	int			num_philo;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			nb_eat;
	int			nb_fork;
	pthread_t	thread;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				*fork;
	t_philo			*philo;
	pthread_mutex_t	*mutex_fork;
}	t_data;

int		nb_of_arg(int ac);
int		parsing(int ac, char **av);

float 	time_diff(struct timeval *start, struct timeval *end);
int		ft_strlen(char *str);
int		ft_atoi(char *str);

void	*ma_routine(void *data);

#endif
