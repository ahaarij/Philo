/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daily_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:48:17 by ahaarij           #+#    #+#             */
/*   Updated: 2024/05/01 15:29:53 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thinky_winky(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	sleepy_weepy(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	usleep_but_instead_of_sleep_its_freaky(philo->time_to_sleep);	
}

void	eaty_weaty(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		usleep_but_instead_of_sleep_its_freaky(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	usleep_but_instead_of_sleep_its_freaky(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
