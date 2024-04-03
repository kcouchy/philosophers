/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:13:46 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/03 17:54:49 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ullong elapsed_ms(t_philo *philo)
{
	struct timeval tv;
	ullong	ms;

	// tv.tv_sec = 0;
	// tv.tv_usec = 0;
	ms = 0;
	gettimeofday(&tv, NULL);
	ms = ((tv.tv_sec - philo->start_sec) * 1000) +
		((tv.tv_usec - philo->start_usec) / 1000);
	// philo->start_sec = tv.tv_sec;
	// philo->start_usec = tv.tv_usec;
	return (ms);
}

int	set_timer(t_philo *philo)
{
	struct timeval tv;

	// tv.tv_sec = 0;
	// tv.tv_usec = 0;
	gettimeofday(&tv, NULL);
	philo->start_sec = tv.tv_sec;
	philo->start_usec = tv.tv_usec;
	// printf("sec: %ld\nusec: %ld\n", tv.tv_sec, tv.tv_usec);
	// while (1)
	// {
	// 	usleep(100000);
	// 	printf ("elapsed ms %lld\n", elapsed_ms(philo));
	// }
	return (0);
}

// code our own usleep to be more precise - why is this more precise?
// void	ft_usleep(ullong time)
// {
// 	struct timeval	tv;
// 	ullong	start;

// 	start = gettimeofday(&tv, NULL);
// 	while ((get_time() - start) < sleep_time)
// 		usleep(500);
// }

// void	ft_usleep(uint64_t sleep_time)
// {
// 	u_int64_t	start;

// 	start = get_time();
// 	while ((get_time() - start) < sleep_time)
// 		usleep(500);
// }

// u_int64_t	get_time(void)
// {
// 	struct timeval	tv;

// 	if (gettimeofday(&tv, NULL))
// 		return (0);
// 	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
// }