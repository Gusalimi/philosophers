/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:14:19 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/06 16:24:53 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr_fd(int fd, char *s)
{
	if (fd < 0 || s == NULL)
	{
		ft_putstr_fd(fd, "(null)");
		return (1);
	}
	write(fd, s, ft_strlen(s));
	return (1);
}
