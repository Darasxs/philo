/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:52:33 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/25 16:35:24 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	usleep_helper(unsigned long m_seconds, t_philo_config *config)
{
	unsigned long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < m_seconds && config->death_flag == false)
		usleep(500);
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_msg(t_philo_config *config, t_philo_details *philo, int id,
		char *str)
{
	unsigned long	time;

	if (philo->config->death_flag)
		return ;
	pthread_mutex_lock(&config->write_lock);
	time = get_time() - philo->starting_time;
	printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(&config->write_lock);
}
