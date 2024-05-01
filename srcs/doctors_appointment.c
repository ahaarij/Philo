/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doctors_appointment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:02:37 by ahaarij           #+#    #+#             */
/*   Updated: 2024/05/01 14:17:02 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (fit_check(philos) == 1 || slayyy(philos) == 1)
			break ;
	return (pointer);
}

int	philo_dieded(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if(get_current_time() - philo->last_meal >= time_to_die 
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	fit_check(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if(philo_dieded(&philos[i], philos[i].time_to_die))
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	slayyy(t_philo *philos)
{
	int	i;
	int	finish_shawarma;

	i = 0;
	finish_shawarma = 0;
	if(philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if(philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finish_shawarma++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finish_shawarma == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}
