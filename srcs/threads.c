/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 09:52:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/28 18:32:37 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*routine(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep_me(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		sleep_msg(philo);
		think(philo);
	}
	return (ptr);
}

int	create_thread(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;
	
	if(pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		free_func("Thread creation error", program, forks);
	i = 0;
	while(i < program->philos[0].num_of_philos)
	{
		if(pthread_create(&program->philos[i].thread, NULL, &routine, &program->philos[i]) != 0)
			free_func("Thread creation error", program, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		free_func("Thread join error", program, forks);
	while(i < program->philos[0].num_of_philos)
	{
		if(pthread_join(program->philos[i].thread, NULL) != 0)
			free_func("Thread join coinkydink", program, forks);
		i++;
	}
	return (0);
}