/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:30 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/11 12:41:13 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_lock(t_main *main, int phil, char *message)
{
	pthread_mutex_lock(&(main)->print_lock);
	printf("%llu %d %s\n", elapsed_time(main), phil, message);
	pthread_mutex_unlock(&(main)->print_lock);
}