/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:13:22 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/05 15:13:09 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		phils[i].r_fork = &(main)->forks[i];
		// printf("phil %d takes fork %d as r_fork\n", phils[i].id, i);
		if (i == 0)
		{
			phils[i].l_fork = &(main)->forks[main->num_phils - 1];
			// printf("phil %d takes fork %d as l_fork\n", phils[i].id, main->num_phils - 1);
		}
		else
		{
			phils[i].l_fork = &(main)->forks[i - 1];
			// printf("phil %d takes fork %d as l_fork\n", phils[i].id, i - 1);
		}
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
	main->phils = phils;
	main->forks = NULL;
	main->forks = malloc(sizeof(pthread_mutex_t) * main->num_phils);
	if (main->forks == NULL)
		return (-1);
	while (++i < main->num_phils)
		pthread_mutex_init(&(main)->forks[i], NULL);
	return (0);
}