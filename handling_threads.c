/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:52:14 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/25 17:37:19 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_death(t_philo_config *philo)
{
	unsigned long	current_time;
	int				i;

	current_time = get_time();
	i = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->meal_lock);
		if (current_time - philo->philos[i].last_meal
			>= (unsigned long)philo->philos[i].config->time_to_die
			&& philo->philos[i].eating == false)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->meal_lock);
		i++;
	}
	return (0);
}

int	died(t_philo_config *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philosophers)
	{
		if (check_philo_death(philo))
		{
			pthread_mutex_lock(&philo->dead_lock);
			philo->philos[i].dead = true;
			print_msg(philo->philos->config, &philo->philos[i],
				philo->philos[i].id, "died");
			philo->death_flag = true;
			pthread_mutex_unlock(&philo->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	finished_eating(t_philo_config *philo)
{
	int	i;
	int	full_check;

	i = 0;
	full_check = 0;
	while (i < philo->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->meal_lock);
		if (philo->philos[i].full == true)
			full_check++;
		pthread_mutex_unlock(&philo->meal_lock);
		i++;
	}
	if (full_check == i)
		return (1);
	return (0);
}

void	*monitoring_function(void *config)
{
	t_philo_config	*config_data;

	config_data = (t_philo_config *)config;
	while (1)
	{
		if (finished_eating(config_data) || died(config_data))
			break ;
	}
	return (config_data);
}

int	create_threads(t_philo_config *config, pthread_mutex_t *forks)
{
	int			i;
	int			j;
	pthread_t	monitor;

	i = 0;
	j = 0;
	if (pthread_create(&monitor, NULL, &monitoring_function, config) != 0)
		destroy_mutexes(config, forks);
	while (i < config->number_of_philosophers)
	{
		if (pthread_create(&config->philos[i].thread, NULL, &philo_cycle,
				&config->philos[i]) != 0)
		{
			destroy_mutexes(config, forks);
			return (1);
		}
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
	{
		destroy_mutexes(config, forks);
		return (2);
	}
	while (j < config->number_of_philosophers)
	{
		if (pthread_join(config->philos[j].thread, NULL) != 0)
		{
			destroy_mutexes(config, forks);
			return (3);
		}
		j++;
	}
	return (0);
}
