/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:13:46 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/04 16:03:05 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
