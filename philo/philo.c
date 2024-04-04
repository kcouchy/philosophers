/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:37:45 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/04 15:18:23 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->num_phils)
	{
		printf("id: %d\n", main->phils[i].id);
		i++;
	}

// create threads to run the thread function
	// pthread_create(&thread2, NULL, deposit, (void*) &deposit2);

// join the threads
	// pthread_join(thread1, NULL);
	// pthread_join(thread2, NULL);

// destroy the mutex
	// pthread_mutex_destroy(&mutex);
}

t_phil	*init_phils(t_main *main, t_phil *phils)
{
	int	i;

	i = 0;
	phils = malloc(sizeof(t_phil) * main->num_phils);
	if (!phils)
		return (NULL);
	while (i < main->num_phils)
	{
		phils[i].id = i + 1;
		phils[i].main = main;
		i++;
	}
	return (phils);
}

int	init_main(t_main *main, t_phil *phils)
{
	int	i;

	i = -1;
	main->phil_dead = 0;
	main->num_eat = -1;
	main->start_time = 0;
	main->start_time = elapsed_time(main);
	if (main->start_time == 0)
		return (-1);
	main->phils = phils;
	main->forks = NULL;
	main->forks = malloc(sizeof(int) * main->num_phils);
	if (main->forks == NULL)
		return (-1);
	while (++i < main->num_phils)
		main->forks[i] = i + 1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	main;
	t_phil *phils;

	phils = NULL;
	if (!((argc == 5 || argc == 6) && check_inputs(argc, argv, &main) == 0))
		return (invalid_input());
	phils = init_phils(&main, phils);
	if (!phils)
		return (printf("initialisation error\n"));
	if (init_main(&main, phils) == -1)
		return (ft_free(2, phils, main.forks), printf("initialisation error\n"));
	ft_philo(&main);
	return (ft_free(2, phils, main.forks), 0);
}