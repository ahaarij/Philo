/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:48:33 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/28 18:27:42 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	exit_msg(char *msg)
{
    if (msg)
	{
        write(2, msg, strlen(msg));
		write(2, "\n", 1);
		exit (1);
	}
	else
    	exit (0);
}

int	main(int argc, char **argv)
{
	t_program	program;
	t_philo		philo[250];
	pthread_mutex_t	forks[250];
	t_rules		rules;
	if(argc != 5 && argc != 6)
		exit_msg("Incorrect amount of arguments!");
	if(check(&rules, argv) != 0)
		return (1);
	init_program(&program, philo);
	init_fork(forks, ft_atoi(argv[1]));
	init_philos(philo, &program, forks, argv);
	create_thread(&program, forks);
	free_func(NULL, &program, forks);
	return (0);
}

// note to self, put explanation for what each function is before i go to india
// or ill forget
