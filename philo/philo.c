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

void	*ft_philo(void *phil)
{
	int	i;

	i = 0;
	while (i < ((t_main *)((t_phil *)phil)->main)->num_phils)
	{
		printf("phil id: %d\n", ((t_phil *)((t_main *)((t_phil *)phil)->main)->phils)[i].id);
		i++;
	}
	return (phil);
}

void	*ft_monitor(void *main)
{
	printf("monitor id: %lu\n", ((t_main *)main)->monitor_id);
	return (main);
}

int	ft_clean(t_main *main, t_phil *phils, char *message, int return_val)
{
	int	i;

	i = -1;
	while (++i < main->num_phils)
		pthread_mutex_destroy(&(main)->forks[i]);
	ft_free(2, phils, main->forks);
	printf("%s\n", message);//ADD PRINT MUTEX HERE?
	return (return_val);
}

//remove error messages from return so that return value can be correct?
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
		return (ft_clean(&main, phils, "malloc error : main", 1));
	//ft_philo(&main);
	return (ft_clean(&main, phils, "", 0));
}