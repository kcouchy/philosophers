/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:19:44 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/03 17:47:35 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>		//printf
# include <sys/time.h>	//gettimeofday
#include <unistd.h>		//usleep

/* ************************************************************************** */
/* typedefs                                                                   */
/* ************************************************************************** */

typedef unsigned long long ullong;

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
	time_t	start_sec;
	suseconds_t start_usec;
}	t_philo;

// struct timeval
// {
// 	time_t		tv_sec;		/* seconds */
// 	suseconds_t	tv_usec;	/* microseconds */
// };

/* ************************************************************************** */
/* check_inputs                                                               */
/* ************************************************************************** */

int		is_int(char *argv);
int		check_inputs(int argc, char **argv, t_philo *philo);
void	invalid_input(void);

/* ************************************************************************** */
/* utils                                                                      */
/* ************************************************************************** */

ullong	elapsed_ms(t_philo *philo);
int		set_timer(t_philo *philo);

#endif