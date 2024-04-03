/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:37:45 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/03 16:45:25 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo(t_philo *philo)
{
	printf("num_phil: %d\n", philo->num_phil);
	printf("time_die: %d\n", philo->time_die);
	printf("time_eat: %d\n", philo->time_eat);
	printf("time_sleep: %d\n", philo->time_sleep);
	printf("num_eat: %d\n", philo->num_eat);
	printf("sec: %ld\nusec: %ld\n", philo->start_sec, philo->start_usec);
}

static void	_init_philo(t_philo *philo)
{
	philo->num_phil = 0;
	philo->time_die = 0;
	philo->time_eat = 0;
	philo->time_sleep = 0;
	philo->num_eat = -1;
	set_timer(philo);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	_init_philo(&philo);
	if ((argc == 5 || argc == 6) && check_inputs(argc, argv, &philo) == 0)
		ft_philo(&philo);
	else
		invalid_input();
	return (0);
}