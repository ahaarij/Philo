/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:43:01 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/28 18:32:10 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_rules
{
	int num_philo;
	int time_death;
	int time_eat;
	int	time_sleep;
	int	num_eat_before_death;
}				t_rules;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;


void	exit_msg(char *msg);
int		check(t_rules *rules, char **argv);
int		ft_atoi(const char *str);
void	init_program(t_program *program, t_philo *philo);
void	init_fork(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks, char **argv);
void	init_input(t_philo *philo, char **argv);
size_t	get_current_time();
int		create_thread(t_program *program, pthread_mutex_t *forks);
void	*monitor(void *pointer);
void	print_message(char *str, t_philo *philo, int id);
int		dead_loop(t_philo *philo);
void 	free_func(char *str, t_program *program, pthread_mutex_t *forks);
int		ft_strlen(char *str);
void	think(t_philo *philo);
void	sleep_msg(t_philo *philo);
void	eat(t_philo *philo);
int		philo_dieded(t_philo *philo, size_t time_to_die);
int		fit_check(t_philo *philos);
int		eaten(t_philo *philos);
int		usleep_me(size_t ms);

#endif