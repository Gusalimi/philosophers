/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:19:12 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/06 16:28:30 by gsaile           ###   ########.fr       */
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
}					t_philo;

int					ft_atoi(const char *str);
int					ft_atoi_test(const char *str);
int					ft_putstr_fd(int fd, char *s);
int					ft_strlen(const char *s);
void				ft_lstclear(t_philo **lst);

#endif