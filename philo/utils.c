/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:13:46 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/11 11:25:14 by kcouchma         ###   ########.fr       */
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
