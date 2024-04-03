/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:19:44 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/03 11:43:41 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>

/* ************************************************************************** */
/* structures                                                                 */
/* ************************************************************************** */

typedef struct s_philo
{
	int	num_phil;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_eat;
}	t_philo;

/* ************************************************************************** */
/* check_inputs                                                               */
/* ************************************************************************** */

int		is_int(char *argv);
int		check_inputs(int argc, char **argv, t_philo *philo);
void	invalid_input(void);

#endif