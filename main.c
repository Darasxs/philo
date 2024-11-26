/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:05:01 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/25 11:49:00 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_philo_config	*config;
	pthread_mutex_t	*forks;

	forks = NULL;
	config = NULL;
	if (argc != 5 && argc != 6)
		print_error("Wrong number of arguments passed.\n");
	else
	{
		if (!arguments_validation(argc, argv))
			return (1);
		config = init_struct(argc, argv, &config, forks);
		if (!config)
		{
			print_error("Failed to initialize the struct.\n");
			return (2);
		}
		if (create_threads(config, forks) != 0)
		{
			print_error("Failed to create threads.\n");
			return (3);
		}
	}
	free_everything(config, forks);
	return (0);
}
