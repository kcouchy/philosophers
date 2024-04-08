/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:19:44 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/08 12:18:15 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>		//printf
# include <sys/time.h>	//gettimeofday
# include <unistd.h>	//usleep
# include <stdlib.h>	//malloc, free
# include <stdarg.h>	//va_args

/* ************************************************************************** */
/* typedefs                                                                   */
/* ************************************************************************** */

typedef unsigned long long ullong;

/* ************************************************************************** */
/* structures                                                                 */
/* ************************************************************************** */

typedef struct s_phil
{
	int				id;
	pthread_mutex_t	*r_fork;		//pointer to the eventual fork mutexes (n && n +/- 1)
	pthread_mutex_t	*l_fork;		//pointer to the eventual fork mutexes (n && n +/- 1)
	pthread_t		thread_id;
	size_t			time_last_eat;
	void			*main;
}	t_phil;

typedef struct s_main
{
	int				phil_dead;
	int				num_phils;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	pthread_mutex_t	*forks;
	size_t			start_time;
	pthread_t		monitor_id;
	// pthread_mutex_t	print_lock;
	// pthread_mutex_t	dead_lock;
	// pthread_mutex_t	meal_lock;
	void			*phils;	//pointer to array of philosophers struct t_phil
}	t_main;

// pthread_t		variable to hold the id of a thread (like pid for forks)
// pthread_mutex_t	mutex type variable - to be locked/unlocked/joined/detached

// struct timeval
// {
// 	time_t		tv_sec;		/* seconds */
// 	suseconds_t	tv_usec;	/* microseconds */
// };

/* ************************************************************************** */
/* check_inputs                                                               */
/* ************************************************************************** */

int		is_int(char *argv);
int		check_inputs(int argc, char **argv, t_main *main);
int		invalid_input(void);

/* ************************************************************************** */
/* utils                                                                      */
/* ************************************************************************** */

int		start_time(t_main *main);
void	ft_free(size_t n, ...);
ullong	elapsed_time(t_main *main);

/* ************************************************************************** */
/* inits                                                                      */
/* ************************************************************************** */

int		init_threads(t_main *main, t_phil *phils);
t_phil	*init_phils(t_main *main, t_phil *phils);
int		init_main(t_main *main, t_phil *phils);

/* ************************************************************************** */
/* philo (main)                                                               */
/* ************************************************************************** */

void	*ft_philo(void *phil);
void	*ft_monitor(void *phil);
int		ft_clean(t_main *main, t_phil *phils, char *message, int return_val);
int		main(int argc, char **argv);

#endif