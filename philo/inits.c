/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:13:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/11 18:59:33 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//make phil threads + monitoring thread
int	init_threads(t_main *main, t_phil *phils)
{
	int	i;

	i = 0;
// create threads to run the thread functions
	if (pthread_create(&main->monitor_id, NULL, &ft_monitor, main) != 0)
		return (ft_clean(main, phils, "pthread_create fail : monitor", 1));
	while (i < main->num_phils)
	{
		if (pthread_create(&((t_phil *)main->phils)[i].thread_id, NULL, &ft_philo, &main->phils[i]) != 0)
			return (ft_clean(main, phils, "pthread_create fail : philosopher", 1));
		i++;
	}
// join the threads to wait for termination before returning main
	if (pthread_join(main->monitor_id, NULL) != 0)
		return (ft_clean(main, phils, "pthread_join fail : monitor", 1));
	i = 0;
	while (i < main->num_phils)
	{
		if (pthread_join(((t_phil *)main->phils)[i].thread_id, NULL) != 0)
			return (ft_clean(main, phils, "pthread_join fail : philosopher", 1));
		i++;
	}
// destroy the mutexes
	return (ft_clean(main, phils, "end of meals", 0));
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
		phils[i].time_last_eat = main->start_time;
		phils[i].num_eat = main->num_eat;
		phils[i].r_fork = &(main)->forks[i];
		if (i == 0)
			phils[i].l_fork = &(main)->forks[main->num_phils - 1];
		else
			phils[i].l_fork = &(main)->forks[i - 1];
		i++;
	}
	return (phils);
}

int	init_main(t_main *main, t_phil *phils)
{
	int	i;

	i = -1;
	main->phil_dead = 0;
	main->phils = phils;
	main->forks = NULL;
	main->forks = malloc(sizeof(pthread_mutex_t) * main->num_phils);
	if (main->forks == NULL)
		return (-1);
	if (pthread_mutex_init(&(main)->print_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(main)->dead_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(main)->num_eat_lock, NULL) != 0)
		return (-1);
	while (++i < main->num_phils)
	{
		if (pthread_mutex_init(&(main)->forks[i], NULL) != 0)
			return (-1);
	}
	return (0);
}
