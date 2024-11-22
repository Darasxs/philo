/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:11:00 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/16 22:52:30 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	size_t	counter;
	long	final;

	counter = 0;
	final = 0;
	if (str == NULL)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		final = final * 10 + (*str - '0');
		str++;
	}
	return (final);
}

bool	is_digit(char *str)
{
	size_t	i;

	if (str == NULL)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		if (str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}
