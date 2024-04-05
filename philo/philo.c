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
	// while (i < main->num_phils)
	// {
	// 	printf("id: %d\n", main->phils[i].id);
	// 	i++;
	// }

//make phil threads + monitoring threads

// create threads to run the thread function
	// pthread_create(&thread2, NULL, deposit, (void*) &deposit2);
	while (i < main->num_phils)
	{
		pthread_create();
		i++;
	}

// join the threads
	// pthread_join(thread1, NULL);
	// pthread_join(thread2, NULL);

// destroy the mutex
	// pthread_mutex_destroy(&mutex);
}

void	ft_clean(t_main *main, t_phil *phils)
{
	int	i;

	i = -1;
	while (++i < main->num_phils)
		pthread_mutex_destroy(&(main)->forks[i]);
	ft_free(2, phils, main->forks);//do i still need to free underlying
}

//will need to remove error messages from return so that return value can be correct
int	main(int argc, char **argv)
{
	t_main	main;
	t_phil *phils;

	phils = NULL;
	if (start_time(&main) == -1)
		return (printf("gettimeofday error : start_time\n"));
	if (!((argc == 5 || argc == 6) && check_inputs(argc, argv, &main) == 0))
		return (invalid_input());
	phils = init_phils(&main, phils);
	if (!phils)
		return (printf("malloc error : phils\n"));
	if (init_main(&main, phils) == -1)
		return (ft_clean(&main, phils), printf("malloc error : main\n"));
	ft_philo(&main);
	return (ft_clean(&main, phils), 0);
}