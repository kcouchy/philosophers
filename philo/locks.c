/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:30 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/11 18:50:49 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_lock(t_main *main, int phil, char *message)
{
	pthread_mutex_lock(&(main)->print_lock);
	if (phil == 0)
		printf("%llu %s\n", elapsed_time(main), message);
	else
		printf("%llu %d %s\n", elapsed_time(main), phil, message);
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