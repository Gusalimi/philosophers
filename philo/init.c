/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:34:29 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/30 10:12:11 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(char **av)
{
	pthread_mutex_t	*forks;
	int				i;
	int				nb_philos;

	nb_philos = ft_atoi(av[1]);
	forks = malloc(nb_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb_philos)
	{
		if (pthread_mutex_init(&(forks[i]), NULL))
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static void	init_philos2(int ac, char **av, pthread_mutex_t *forks,
	t_philo *philo)
{
	philo->finished = 0;
	philo->nb_philos = ft_atoi(av[1]);
	philo->die = ft_atoi(av[2]);
	philo->eat = ft_atoi(av[3]);
	philo->sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->rounds = ft_atoi(av[5]);
	else
		philo->rounds = -1;
	philo->last_meal = 0;
	philo->meals = 0;
	philo->forks = forks;
}

t_philo	*init_philos(int ac, char **av, pthread_mutex_t *forks, int nb_philos)
{
	int			i;
	t_philo		*philos;

	philos = malloc(nb_philos * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < nb_philos)
	{
		philos[i].index = i + 1;
		init_philos2(ac, av, forks, &(philos[i]));
		if (pthread_create(&(philos[i].philo), NULL, &philo, &(philos[i])))
		{
			free(forks);
			free(philos);
			return (NULL);
		}
		usleep(100);
		i++;
	}
	return (philos);
}

t_philo	*detach_philos(t_philo *philos, int nb_philos, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (!philos)
		return (NULL);
	while (i < nb_philos)
	{
		if (pthread_detach(philos[i].philo))
		{
			free(forks);
			free(philos);
			return (NULL);
		}
		usleep(100);
		i++;
	}
	return (philos);
}

t_philo	*init_data(int ac, char **av, pthread_mutex_t *forks)
{
	t_philo			*philos;
	int				nb_philos;

	nb_philos = ft_atoi(av[1]);
	if (nb_philos < 1)
	{
		ft_putstr_fd(2, "Must have at least one philosopher\n");
		return (NULL);
	}
	if (ft_atoi(av[2]) <= 0)
	{
		ft_putstr_fd(2, "Invalid death time\n");
		return (NULL);
	}
	philos = init_philos(ac, av, forks, nb_philos);
	return (detach_philos(philos, nb_philos, forks));
}
