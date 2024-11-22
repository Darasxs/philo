/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:09 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/22 18:08:24 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	arguments_validation(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
		{
			print_error("An argument must be positive numbers only.\n");
			return (false);
		}
		if (ft_atol(argv[i]) > INT_MAX)
		{
			print_error("Numbers must be smaller than INT MAX.\n");
			return (false);
		}
		i++;
	}
	if (ft_atol(argv[1]) > 200)
	{
		print_error("The number of philosophers should not exceed 200.\n");
		return (false);
	}
	return (true);
}

t_philo_config	*init_philo_details(t_philo_config *config,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	config->philos = malloc(sizeof(t_philo_details)
			* config->number_of_philosophers);
	if (!config->philos)
		return (NULL);
	while (i < config->number_of_philosophers)
	{
		config->philos[i].id = i + 1;
		config->philos[i].meals = 0;
		config->philos[i].eating = false;
		config->philos[i].death_flag = false;
		config->philos[i].full = false;
		config->philos[i].starting_time = get_time();
		config->philos[i].last_meal = get_time();
		config->philos[i].config = config;
		config->philos[i].left_fork = &forks[i];
		config->philos[i].right_fork = &forks[(i + 1)
			% config->number_of_philosophers];
		i++;
	}
	return (config);
}

void	init_other_mutexes(t_philo_config *config)
{
	pthread_mutex_init(&config->write_lock, NULL);
	pthread_mutex_init(&config->meal_lock, NULL);
	pthread_mutex_init(&config->dead_lock, NULL);
}

void	mutex_init(pthread_mutex_t **forks, t_philo_config *config)
{
	int	i;

	i = 0;
	*forks = malloc(sizeof(pthread_mutex_t) * config->number_of_philosophers);
	if (!*forks)
	{
		free(config);
		print_error("Error with allocating memory for forks\n");
		return ;
	}
	while (i < config->number_of_philosophers)
	{
		pthread_mutex_init(&(*forks)[i], NULL);
		i++;
	}
	init_other_mutexes(config);
}

t_philo_config	*init_struct(int argc, char **argv,
		t_philo_config *config, pthread_mutex_t *forks)
{
	config = malloc(sizeof(t_philo_config));
	if (!config)
		return (NULL);
	config->number_of_philosophers = ft_atol(argv[1]);
	config->time_to_die = ft_atol(argv[2]);
	config->time_to_eat = ft_atol(argv[3]);
	config->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		config->eating_times = ft_atol(argv[5]);
	else
		config->eating_times = -1;
	mutex_init(&forks, config);
	config = init_philo_details(config, forks);
	if (!config->philos)
	{
		print_error("Failed to initialize philosophers.\n");
		if (config)
			free(config);
		return (NULL);
	}
	return (config);
}
