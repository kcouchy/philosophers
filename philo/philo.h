/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:19:44 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/11 18:55:14 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>		//printf
# include <sys/time.h>	//gettimeofday
# include <unistd.h>	//usleep
# include <stdlib.h>	//malloc, free
# include <stdarg.h>	//va_args
# include <semaphore.h>	//semaphore

/* ************************************************************************** */
/* typedefs                                                                   */
/* ************************************************************************** */

typedef unsigned long long	t_ullong;

/* ************************************************************************** */
/* structures                                                                 */
/* ************************************************************************** */

typedef struct s_phil		t_phil;

typedef struct s_main
{
	int				phil_dead;
	int				num_phils;
	t_ullong		time_die;
	t_ullong		time_eat;
	t_ullong		time_sleep;
	int				num_eat;
	pthread_mutex_t	*forks;
	t_ullong		start_time;
	pthread_t		monitor_id;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	num_eat_lock;
	t_phil			*phils;	//pointer to array of philosophers struct t_phil
}	t_main;

struct s_phil
{
	int				id;
	pthread_mutex_t	*r_fork;		//pointer to the eventual fork mutexes (n && n +/- 1)
	pthread_mutex_t	*l_fork;		//pointer to the eventual fork mutexes (n && n +/- 1)
	pthread_t		thread_id;
	t_ullong		time_last_eat;
	int				num_eat;
	t_main			*main;
};

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

int			is_int(char *argv);
int			check_inputs(int argc, char **argv, t_main *main);
int			invalid_input(void);

/* ************************************************************************** */
/* inits                                                                      */
/* ************************************************************************** */

int			init_threads(t_main *main, t_phil *phils);
t_phil		*init_phils(t_main *main, t_phil *phils);
int			init_main(t_main *main, t_phil *phils);

/* ************************************************************************** */
/* utils                                                                      */
/* ************************************************************************** */

int			start_time(t_main *main);
void		ft_free(size_t n, ...);
t_ullong	elapsed_time(t_main *main);

/* ************************************************************************** */
/* monitor                                                                    */
/* ************************************************************************** */

// static int	_check_death(t_main *main);
// static int	_check_num_eat(t_main *main);
void		*ft_monitor(void *data);

/* ************************************************************************** */
/* locks                                                                      */
/* ************************************************************************** */

/**
 * @brief 
 * 
 * @param main 
 * @param phil 
 * @param message 
 */
void	print_lock(t_main *main, int phil, char *message);

/**
 * @brief To check or modify the flag at main->phil_dead which indicates a 
 * philosopher has died (1) or not (0).
 * locks main->dead_lock mutex
 * Checks the variable main->phil_dead
 * If mod != -1, sets main->phil_dead = mod
 * If mod == -1, returns just the phil_dead
 * @param main pointer to main to access mutex
 * @param mod flag to modify or not phil_dead, and the value to set
 * @return int 
 */
int		phil_dead_lock(t_main *main, int mod);

/**
 * @brief To check or modify the variable phil->num_eat which stores the number
 * of times a philopher has left to eat (starts at main->num_eat)
 * locks main->num_eat_lock mutex
 * Checks the variable phil[i]->num_eat sent as *phil
 * If mod != -1, decrements num_eat before returning the new value
 * If mod == -1, returns just the num_eat
 * @param main pointer to main to access mutex
 * @param phil pointer to a philospher = phil[i] in the structure array
 * @param mod flag to modify or not num_eat
 * @return int value of phil->num_eat
 */
int		num_eat_lock(t_main *main, t_phil *phil, int mod);

/* ************************************************************************** */
/* philo (main)                                                               */
/* ************************************************************************** */

void		*ft_philo(void *data);
void		*ft_monitor(void *data);
int			ft_clean(t_main *main, t_phil *phils, char *message, int ret_val);
int			main(int argc, char **argv);

#endif