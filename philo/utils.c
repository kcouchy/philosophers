/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:13:46 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/16 18:10:14 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_time(t_main *main)
{
	main->start_time = 0;
	main->start_time = elapsed_time(main);
	if (main->start_time == 0)
		return (-1);
	return (0);
}

//may need to add an if 0 to this to pick up when gettimeofday fails
t_ullong	elapsed_time(t_main *main)
{
	t_ullong		ms;
	struct timeval	tv;

	ms = 0;
	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms - main->start_time);
}

void	ft_free(size_t n, ...)
{
	va_list	args;
	void	*arg;

	va_start(args, n);
	while (n)
	{
		arg = va_arg(args, void *);
		if (arg)
			free(arg);
		n--;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] != s2[i]);
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
	if (main->num_eat == 0)
		printf("%s\n", message);
	return (return_val);
}
