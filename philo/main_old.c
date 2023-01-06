/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:04:45 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/02 14:16:14 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chrono(void)
{
	static struct timeval	start;
	struct timeval			t;
	int						elapsedTime;

	gettimeofday(&t, NULL);
	if (start.tv_usec == 0 && start.tv_sec == 0)
		start = t;
	// compute and print the elapsed time in millisec
	elapsedTime = (t.tv_sec - start.tv_sec) * 1000;    // sec to ms
	elapsedTime += (t.tv_usec - start.tv_usec) / 1000; // us to ms
	return (elapsedTime);
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

t_philo	*init(int ac, char **av, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->nb_philo = ft_atoi(av[1]);
	philo->die = ft_atoi(av[2]);
	philo->eat = ft_atoi(av[3]);
	philo->sleep = ft_atoi(av[4]);
	philo->last_meal = 0;
	philo->index = index + 1;
	if (ac == 6)
		philo->meals = ft_atoi(av[5]);
	else
		philo->meals = -1;
	return (philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->index % 2 == 0)
		usleep(150);
	while (philo->meals != 0)
	{
		pthread_mutex_lock(&(philo->fork));
		printf("%d %d grabs fork\n", chrono(), philo->index);
		// printf("%d : current = %p | current->next = %p\n", philo->index,
		//philo, philo->next);
		pthread_mutex_lock(&(philo->next->fork));
		printf("%d %d grabs fork\n", chrono(), philo->index);
		printf("%d %d eats\n", chrono(), philo->index);
		usleep(philo->eat * 1000);
		philo->meals--;
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->next->fork));
		printf("%d %d sleeps\n", chrono(), philo->index);
		usleep(philo->sleep * 1000);
		printf("%d %d thinks\n", chrono(), philo->index);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*head;
	t_philo	*current;
	int		i;

	i = 1;
	if (check_args(ac, av) != NULL)
		return (ft_putstr_fd(2, check_args(ac, av)));
	chrono();
	head = init(ac, av, 0);
	if (head == NULL)
		return (ft_putstr_fd(2, "Malloc failed.\n"));
	if (pthread_create(&(head->philo), NULL, &routine, head) != 0)
		return (1);
	current = head;
	while (i <= head->nb_philo)
	{
		if (i == head->nb_philo)
		{
			current->next = head;
			i++;
		}
		else
		{
			current->next = init(ac, av, i);
			printf("init : %p\n", init(ac, av, i));
			if (!current->next)
			{
				ft_lstclear(&head);
				return (1);
			}
			current = current->next;
			i++;
		}
		usleep(150);
	}
	current = head;
	for (int i = 0; i < head->nb_philo; i++)
	{
		if (pthread_create(&(current->philo), NULL, &routine, current) != 0
			|| pthread_mutex_init(&(current->fork), NULL) != 0)
		{
			ft_lstclear(&head);
			return (1);
		}
		current = current->next;
	}
	current = head;
	for (int i = 0; i < head->nb_philo; i++)
	{
		pthread_join(current->philo, NULL);
		current = current->next;
	}
	current = head;
	for (int i = 0; i < head->nb_philo; i++)
	{
		pthread_detach(current->philo);
		current = current->next;
	}
	return (0);
}
