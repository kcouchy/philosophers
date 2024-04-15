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

// even numbered philos wait half the eat time before trying to grab a fork to 
// avoid deadlocks
void	*ft_philo(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	// print_lock(phil->main, 0, "phil_thread");
	// printf("phil %d\n", phil->id);
	if (phil->id % 2 == 0)
		usleep(phil->time_wait);
	// printf("%d\n", phil_dead_lock(phil->main, -1));
	// printf("num eat%d\n", num_eat_lock(phil->main, phil, -1));
	while (phil_dead_lock(phil->main, -1) == 0
			&& num_eat_lock(phil->main, phil, -1) != 0)
	{
		eat_lock(phil);
		if (phil_dead_lock(phil->main, -1) == 0)
		{
			print_lock(phil->main, phil->id, "is sleeping");
			usleep(phil->main->time_sleep * 1000);
		}
		if (phil_dead_lock(phil->main, -1) == 0)
			print_lock(phil->main, phil->id, "is thinking");
	}
	return (phil);
}

int	ft_clean(t_main *main, t_phil *phils, char *message, int return_val)
{
	int	i;

	i = -1;
	while (++i < main->num_phils)
		pthread_mutex_destroy(&(main)->forks[i]);
	pthread_mutex_destroy(&(main)->print_lock);
	pthread_mutex_destroy(&(main)->dead_lock);
	pthread_mutex_destroy(&(main)->num_eat_lock);
	pthread_mutex_destroy(&(main)->last_eat_lock);
	ft_free(2, phils, main->forks);
	if (main->num_eat != -1)
		print_lock(main, 0, message);
	return (return_val);
}

//remove error messages from return so that return value can be correct?
int	main(int argc, char **argv)
{
	t_main	main;
	t_phil	*phils;

	phils = NULL;
	if (start_time(&main) == -1)
		return (printf("gettimeofday error : start_time\n"));
	if (!((argc == 5 || argc == 6) && check_inputs(argc, argv, &main) == 0))
		return (invalid_input());
	phils = init_phils(&main, phils);
	if (!phils)
		return (printf("malloc error : phils\n"));
	if (init_main(&main, phils) == -1)
		return (ft_clean(&main, phils, "malloc error : main", 1));
	return (init_threads(&main, phils));
}
