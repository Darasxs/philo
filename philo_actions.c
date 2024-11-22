/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:08:32 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/22 18:08:31 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo_details *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo->config, philo, philo->id, "has taken a right fork");
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo->config, philo, philo->id, "has taken a left fork");
	philo->eating = true;
	print_msg(philo->config, philo, philo->id, "is eating");
	pthread_mutex_lock(&philo->config->meal_lock);
	philo->meals++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->config->meal_lock);
	usleep_helper(philo->config->time_to_eat);
	philo->eating = false;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_think(t_philo_details *philo)
{
	print_msg(philo->config, philo, philo->id, "is thinking");
}

void	philo_sleep(t_philo_details *philo)
{
	print_msg(philo->config, philo, philo->id, "is sleeping");
	usleep_helper(philo->config->time_to_sleep);
}

void	*philo_cycle(void *data)
{
	t_philo_details	*philo_details;

	philo_details = (t_philo_details *)data;
	if (philo_details->config->number_of_philosophers == 1)
	{
		print_msg(philo_details->config, philo_details, philo_details->id,
			"has taken a fork");
		return(NULL);
	}
	if (philo_details->id % 2 == 0)
		usleep(500);
	while (1)
	{
		philo_eat(philo_details);
		pthread_mutex_lock(&philo_details->config->meal_lock);
		if (philo_details->meals == philo_details->config->eating_times)
		{
			philo_details->full = true;
			pthread_mutex_unlock(&philo_details->config->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&philo_details->config->meal_lock);
		philo_sleep(philo_details);
		philo_think(philo_details);
	}
	return (data);
}
