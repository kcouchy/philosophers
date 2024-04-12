/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:12:58 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/12 15:54:12 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	_check_death(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->num_phils)
	{
		// usleep(5000);
		// printf("%llu - %llu > %llu = %llu\n", elapsed_time(main), time_last_eat_lock(main, &(main)->phils[i], -1), main->time_die, (elapsed_time(main) - time_last_eat_lock(main, &(main)->phils[i], -1)));
		if ((elapsed_time(main) - time_last_eat_lock(main, &(main)->phils[i], -1)) > main->time_die)
		{
			phil_dead_lock(main, 1);
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
		if (num_eat_lock(main, &(main)->phils[i], -1) != 0)
			return (0);
		i++;
	}
	main->num_eat = 0; //NEED A MUTEX HERE? should only be used in the monitor thread
	return (1);
}

// loops while phil_dead stays 0, checks for death in phils, returns in case of death
void	*ft_monitor(void *data)
{
	t_main	*main;

	main = (t_main *)data;
	while (1)
	{
		if (_check_death(main) != 0 || _check_num_eat(main) != 0)
			break ;
	}
	return (main);
}
