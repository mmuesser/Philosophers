/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:37:48 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/14 17:57:21 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/*changer nom time_die*/

typedef struct s_philo
{
	int				dead;
	long long		time;
	int				num_philo;
	long long		time_die;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				nb_must_eat;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_fork_right;
	pthread_mutex_t mutex_fork_left;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	long long		time;
	t_philo			*philo;
	pthread_mutex_t	*mutex_fork;
}	t_data;

int			nb_of_arg(int ac);
int			parsing(int ac, char **av);

long long	time_passed(long long time);
int			ft_strlen(char *str);
int			ft_atoi(char *str);

void		*ma_routine(void *data);

#endif
