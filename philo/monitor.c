/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:12:58 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/11 12:42:41 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_check_death(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->num_phils)
	{
		if ((elapsed_time(main) - main->phils[i].time_last_eat) > main->time_die)
		{
			main->phil_dead = 1;
			print_lock(main, i + 1, "died");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	_check_num_eat(t_main *main)
{
	int	i;

	i = 0;
	if (main->num_eat == -1)
		return (0);
	while (i < main->num_phils)
	{
		if (main->phils[i].num_eat != 0)
			return (0);
		i++;
	}
	return (1);
}

// loops while phil_dead stays 0, checks for death in phils, returns in case of death
void	*ft_monitor(void *data)
{
	t_main	*main;

	main = (t_main *)data;
	// printf("monitor id: %lu\n", main->monitor_id);
	printf("**********************start time : %llu\n", main->start_time);
	printf("**********************elapsed time : %llu\n", elapsed_time(main));
	printf ("========================%p\n", data);
	printf("**********************last eat : %llu\n", main->phils->time_last_eat);
	while (1)
	{
		if (_check_death(main) != 0 || _check_num_eat(main) != 0)
			break ;
	}
	return (main);
}
