/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 08:37:24 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/28 18:30:58 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check(t_rules *rules, char **argv)
{
	rules->num_philo = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	if (rules->num_philo < 1 || rules->time_death < 0 || rules->time_eat < 0
		|| rules->time_sleep < 0 || rules->num_philo > 250)
		exit_msg("Parameters invalid!");
	if (argv[5])
	{
		rules->num_eat_before_death = ft_atoi(argv[5]);
		if (rules->num_eat_before_death <= 0)
			exit_msg("Parameters invalid!");
	}
	return (0);
}

size_t	get_current_time()
{
	struct timeval time;
	
	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(char *str, t_philo *philo, int id)
{
	size_t time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	usleep_me(size_t ms)
{
	size_t start;

	start = get_current_time();
	while((get_current_time() - start) < ms)
		usleep(500);
	return (0);
}

void free_func(char *str, t_program *program, pthread_mutex_t *forks)
{
	int i;
	
	i = 0;
	if(str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->write_lock);
	while(i < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}