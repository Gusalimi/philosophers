/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaile <gsaile@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:51:59 by gsaile            #+#    #+#             */
/*   Updated: 2023/01/30 09:57:24 by gsaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(int c)
{
	return ((c == '\t') || (c == '\n') || (c == '\v') || (c == '\f')
		|| (c == '\r') || (c == ' '));
}

int	ft_atoi(const char *str)
{
	unsigned int	result;
	char			*tmp;

	result = 0;
	tmp = (char *)str;
	while (ft_isspace(*tmp))
		tmp++;
	if (*tmp == '+')
		tmp++;
	while (ft_isdigit(*tmp))
	{
		result *= 10;
		result += *tmp - '0';
		tmp++;
	}
	return (result);
}

int	ft_atoi_test(const char *str)
{
	unsigned int	result;

	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		return (0);
	if (*str == '+')
		str++;
	if (*str == 0)
		return (0);
	while (ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		if (result > 2147483647)
			return (0);
		str++;
	}
	if (*str != 0)
		return (0);
	return (1);
}
