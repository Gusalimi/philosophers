/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:41:52 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/30 10:09:06 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chrono(void)
{
	static struct timeval	start;
	struct timeval			t;
	int						elapsed;

	gettimeofday(&t, NULL);
	if (start.tv_usec == 0 && start.tv_sec == 0)
		start = t;
	elapsed = (t.tv_sec - start.tv_sec) * 1000;
	elapsed += (t.tv_usec - start.tv_usec) / 1000;
	return (elapsed);
}

void	ft_sleep(int time, t_philo *philo)
{
	int	start;

	start = chrono();
	while (chrono() < start + time)
	{
		if (chrono() - philo->last_meal >= philo->die)
		{
			printf("%d %d died\n", chrono(), philo->index);
			exit(0);
		}
		usleep(500);
	}
}

void	set_finished(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_philos)
		philos[i++].finished = 1;
}

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!philo->finished
		&& (philo->rounds == -1 || philo->meals < philo->rounds))
	{
		pthread_mutex_lock(&(philo->forks[philo->index - 1]));
		printf("%d %d has taken a fork\n", chrono(), philo->index);
		pthread_mutex_lock(&(philo->forks[philo->index % philo->nb_philos]));
		printf("%d %d has taken a fork\n", chrono(), philo->index);
		printf("%d %d is eating\n", chrono(), philo->index);
		philo->last_meal = chrono();
		ft_sleep(philo->eat, philo);
		philo->meals++;
		pthread_mutex_unlock(&(philo->forks[philo->index - 1]));
		pthread_mutex_unlock(&(philo->forks[(philo->index)
				% philo->nb_philos]));
		printf("%d %d is sleeping\n", chrono(), philo->index);
		ft_sleep(philo->sleep, philo);
		printf("%d %d is thinking\n", chrono(), philo->index);
	}
	return (NULL);
}
