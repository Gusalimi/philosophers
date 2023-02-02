/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:52:06 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/30 10:04:43 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_philos_ate(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos[0].rounds == -1)
		return (0);
	while (i < philos[0].nb_philos)
	{
		if (philos[i].meals < philos[i].rounds)
			return (0);
		i++;
	}
	return (1);
}

static char	*check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return ("Wrong number of arguments.\n");
	while (i < ac)
		if (ft_atoi_test(av[i++]) == 0)
			return ("Arguments must be positive numbers and fit in an int.\n");
	return (NULL);
}

static int	loop(t_philo *philos)
{
	int	i;

	while (1)
	{
		i = 0;
		if (all_philos_ate(philos))
			break ;
		while (i < philos[0].nb_philos)
		{
			if (chrono() - philos[i].last_meal >= philos[i].die)
			{
				set_finished(philos);
				printf("%d %d died\n", chrono(), philos[i].index);
				return (1);
			}
			i++;
		}
		usleep(250);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (check_args(ac, av) != NULL)
		return (ft_putstr_fd(2, check_args(ac, av)));
	forks = init_forks(av);
	if (!forks)
		return (1);
	philos = init_data(ac, av, forks);
	if (!philos)
	{
		free(forks);
		return (1);
	}
	loop(philos);
	free(philos);
	free(forks);
	return (0);
}
