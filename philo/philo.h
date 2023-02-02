/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:19:12 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/29 16:45:53 by gsaile           ###   ########.fr       */
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
	pthread_t		philo;
	pthread_mutex_t	*forks;
	int				nb_philos;
	int				meals;
	int				sleep;
	int				eat;
	int				die;
	int				rounds;
	int				last_meal;
	int				index;
	int				finished;
}					t_philo;

/* - - - - - ft_atoi.c - - - - - */
int					ft_atoi(const char *str);
int					ft_atoi_test(const char *str);

/* - - - - - ft_putstr_fd.c - - - - - */
int					ft_putstr_fd(int fd, char *s);
int					ft_strlen(const char *s);

/* - - - - - init.c - - - - - */
t_philo				*init_data(int ac, char **av, pthread_mutex_t *forks);
pthread_mutex_t		*init_forks(char **av);
t_philo				*init_philos(int ac, char **av, pthread_mutex_t *forks,
						int nb_philos);
t_philo				*detach_philos(t_philo *philos, int nb_philos,
						pthread_mutex_t *forks);

/* - - - - - utils.c - - - - - */
int					chrono(void);
void				ft_sleep(int time, t_philo *philo);
void				set_finished(t_philo *philos);
void				*philo(void *arg);

#endif