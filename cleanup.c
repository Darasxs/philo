/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:41:24 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/17 17:01:00 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_philo_config *config, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&config->write_lock);
	pthread_mutex_destroy(&config->meal_lock);
	pthread_mutex_destroy(&config->dead_lock);
}

