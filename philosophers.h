/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:48:39 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/11/25 16:34:20 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_config	t_philo_config;

typedef struct s_philo_details
{
	pthread_t					thread;
	int							id;
	int							dead;
	int							meals;
	bool						eating;
	bool						full;
	unsigned long				starting_time;
	unsigned long				last_meal;
	pthread_mutex_t				*right_fork;
	pthread_mutex_t				*left_fork;
	t_philo_config				*config;
}								t_philo_details;

typedef struct s_philo_config
{
	int							number_of_philosophers;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							eating_times;
	bool						death_flag;
	pthread_mutex_t				write_lock;
	pthread_mutex_t				meal_lock;
	pthread_mutex_t				dead_lock;
	t_philo_details				*philos;
}								t_philo_config;

// general
int								main(int argc, char **argv);

// utils
size_t							ft_strlen(char *str);
long							ft_atol(char *str);
bool							is_digit(char *str);

// helper functions
unsigned long					get_time(void);
unsigned long					usleep_helper(unsigned long m_seconds,
									t_philo_config *config);
void							print_msg(t_philo_config *config,
									t_philo_details *philo, int id, char *str);

// preparation
t_philo_config					*init_struct(int argc, char **argv,
									t_philo_config **config,
									pthread_mutex_t *forks);
bool							arguments_validation(int argc, char **argv);
t_philo_config					*init_philo_details(t_philo_config **config,
									pthread_mutex_t *forks);
void							mutex_init(pthread_mutex_t **forks,
									t_philo_config **config);
void							init_other_mutexes(t_philo_config **config);

// main logic
int								create_threads(t_philo_config *config,
									pthread_mutex_t *forks);
void							*monitoring_function(void *config);
int								finished_eating(t_philo_config *philo);
int								check_philo_death(t_philo_config *philo);
int								died(t_philo_config *philo);

// philo actions
void							*philo_cycle(void *data);
void							philo_sleep(t_philo_details *philo);
void							philo_think(t_philo_details *philo);
void							philo_eat(t_philo_details *philo);

// cleanup and error handling
void							print_error(char *message);
void							destroy_mutexes(t_philo_config *config,
									pthread_mutex_t *forks);
void							free_everything(t_philo_config *config,
									pthread_mutex_t *forks);

#endif