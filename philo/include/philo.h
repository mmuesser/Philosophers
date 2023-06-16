/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuesser <mmuesser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:37:48 by mmuesser          #+#    #+#             */
/*   Updated: 2023/06/16 14:42:15 by mmuesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num_philo;
	int				*dead;
	long long		time;
	long long		time_last_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				nb_must_eat;
	pthread_mutex_t	mutex_nb_eat;
	pthread_mutex_t	mutex_time_last_eat;
	pthread_mutex_t	*mutex_printf;
	pthread_mutex_t	*mutex_dead;
	pthread_mutex_t	*mutex_fork_right;
	pthread_mutex_t	*mutex_fork_left;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				dead;
	int				nb_philo;
	long long		time;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	*mutex_fork;
	t_philo			*philo;
}	t_data;

int				nb_of_arg(int ac);
int				parsing(int ac, char **av);

void			print(t_philo *philo, int i);
void			wait_thread(t_data *data, int nb);
long long		time_passed(long long time);
int				ft_strlen(char *str);
int				ft_atoi(char *str);

int				check_death(t_philo *philo);
void			*routine_multiple_philo(void *data);
void			*routine_one_philo(void *arg);

t_philo			*set_philo(int ac, char **av, t_data *data);
pthread_mutex_t	*set_mutex_fork(int nb);
t_data			*set_data(int ac, char **av);

void			free_all(t_data *data);

#endif
