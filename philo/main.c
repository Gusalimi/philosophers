/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:52:06 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/06 17:00:36 by gsaile           ###   ########.fr       */
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
	}
}

char	*check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return ("Wrong number of arguments.\n");
	while (i < ac)
		if (ft_atoi_test(av[i++]) == 0)
			return ("Arguments must be positive numbers only.\n");
	return (NULL);
}

void	*philo(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->rounds == -1 || philo->meals < philo->rounds)
	{
		pthread_mutex_lock(&(philo->forks[philo->index]));
		printf("%d %d has taken a fork\n", chrono(), philo->index);
		pthread_mutex_lock(&(philo->forks[(philo->index + 1)
				% philo->nb_philos]));
		printf("%d %d has taken a fork\n", chrono(), philo->index);
		printf("%d %d is eating\n", chrono(), philo->index);
		philo->last_meal = chrono();
		ft_sleep(philo->eat, philo);
		philo->meals++;
		pthread_mutex_unlock(&(philo->forks[philo->index]));
		pthread_mutex_unlock(&(philo->forks[(philo->index + 1)
				% philo->nb_philos]));
		printf("%d %d is sleeping\n", chrono(), philo->index);
		ft_sleep(philo->sleep, philo);
		printf("%d %d is thinking\n", chrono(), philo->index);
	}
	return (NULL);
}

t_philo	*init_data(int ac, char **av)
{
	t_philo			*philos;
	int				nb_philos;
	int				i;
	pthread_mutex_t	*forks;

	nb_philos = ft_atoi(av[1]);
	if (nb_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(1000 * ft_atoi(av[2]));
		printf("%d 1 died\n", ft_atoi(av[2]));
		return (NULL);
	}
	philos = malloc(nb_philos * sizeof(t_philo));
	if (!philos)
		return (NULL);
	forks = malloc(nb_philos * sizeof(pthread_mutex_t));
	if (!forks)
	{
		free(philos);
		return (NULL);
	}
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_mutex_init(&(forks[i]), NULL))
		{
			free(forks);
			free(philos);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		philos[i].nb_philos = ft_atoi(av[1]);
		philos[i].die = ft_atoi(av[2]);
		philos[i].eat = ft_atoi(av[3]);
		philos[i].sleep = ft_atoi(av[4]);
		if (ac == 6)
			philos[i].rounds = ft_atoi(av[5]);
		else
			philos[i].rounds = -1;
		philos[i].index = i + 1;
		philos[i].last_meal = 0;
		philos[i].meals = 0;
		philos[i].forks = forks;
		philos[i].nb_philos = nb_philos;
		if (pthread_create(&(philos[i].philo), NULL, &philo, &(philos[i])))
		{
			free(forks);
			free(philos);
			return (NULL);
		}
		usleep(10);
		i++;
	}
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_join(philos[i].philo, NULL))
		{
			free(philos);
			free(fork);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (check_args(ac, av) != NULL)
		return (ft_putstr_fd(2, check_args(ac, av)));
	philos = init_data(ac, av);
}
