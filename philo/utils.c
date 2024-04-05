/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:13:46 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/05 12:26:00 by kcouchma         ###   ########.fr       */
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

ullong	elapsed_time(t_main *main)
{
	ullong	ms;
	struct timeval tv;

	ms = 0;
	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms - main->start_time);
}

//add null check?
void	ft_free(size_t n, ...)
{
	va_list	args;

	va_start(args, n);
	while (n)
	{
		free(va_arg(args, void *));
		n--;
	}
}