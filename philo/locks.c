/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:30 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/17 12:32:05 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_lock(t_main *main, int phil, char *message)
{
	pthread_mutex_lock(&(main)->print_lock);
	if (main->print_flag == 0)
	{
		if (phil == 0)
		{
			printf("%llu %s\n", elapsed_time(main), message);
			main->print_flag = 1;
		}
		else if (ft_strcmp("died", message) == 0)
		{
			printf("%llu %d %s\n", elapsed_time(main), phil, message);
			main->print_flag = 1;
		}
		else
			printf("%llu %d %s\n", elapsed_time(main), phil, message);
	}
	pthread_mutex_unlock(&(main)->print_lock);
}

int	phil_dead_lock(t_main *main, int mod)
{
	int	phil_dead;

	pthread_mutex_lock(&(main)->dead_lock);
	if (mod != -1)
		main->phil_dead = mod;
	phil_dead = main->phil_dead;
	pthread_mutex_unlock(&(main)->dead_lock);
	return (phil_dead);
}

int	num_eat_lock(t_main *main, t_phil *phil, int mod)
{
	int	num_eat;

	pthread_mutex_lock(&(main)->num_eat_lock);
	if (mod != -1)
		phil->num_eat--;
	num_eat = phil->num_eat;
	pthread_mutex_unlock(&(main)->num_eat_lock);
	return (num_eat);
}

t_ullong	time_last_eat_lock(t_main *main, t_phil *phil, int mod)
{
	t_ullong	time_last_eat;

	pthread_mutex_lock(&(main)->last_eat_lock);
	if (mod != -1)
		phil->time_last_eat = elapsed_time(main);
	time_last_eat = phil->time_last_eat;
	pthread_mutex_unlock(&(main)->last_eat_lock);
	return (time_last_eat);
}

int	eat_lock(t_phil *phil)
{
	if (phil_dead_lock(phil->main, -1) == 0)
	{
		pthread_mutex_lock(phil->r_fork);
		print_lock(phil->main, phil->id, "has taken a fork");
	}
	if (phil->r_fork == phil->l_fork)
	{
		pthread_mutex_unlock(phil->r_fork);
		return (1);
	}
	if (phil_dead_lock(phil->main, -1) == 0)
	{
		pthread_mutex_lock(phil->l_fork);
		print_lock(phil->main, phil->id, "has taken a fork");
		if (phil_dead_lock(phil->main, -1) == 0)
		{
			time_last_eat_lock(phil->main, phil, 1);
			print_lock(phil->main, phil->id, "is eating");
			usleep(phil->main->time_eat * 1000);
			num_eat_lock(phil->main, phil, 1);
		}
		pthread_mutex_unlock(phil->l_fork);
	}
	pthread_mutex_unlock(phil->r_fork);
	return (0);
}
