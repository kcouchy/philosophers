/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:19:44 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/15 16:48:39 by kcouchma         ###   ########.fr       */
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
	int				phil_dead;		//flag to
	int				num_phils;
	t_ullong		time_die;
	t_ullong		time_eat;
	t_ullong		time_sleep;
	int				num_eat;		//flag = 0 when all phils->num_eat = 0
	pthread_mutex_t	*forks;			//pointer to array of pthread_mutex_t
	t_ullong		start_time;
	pthread_t		monitor_id;		//id for threadjoin
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	num_eat_lock;
	pthread_mutex_t	last_eat_lock;
	t_phil			*phils;			//pointer to array of philosophers t_phil
}	t_main;

struct s_phil
{
	int				id;				//number of philosopher [i + 1]
	pthread_mutex_t	*r_fork;		//pointer to the fork mutex (fork[n])
	pthread_mutex_t	*l_fork;		//pointer to the fork mutex (fork[n-1])
	pthread_t		thread_id;		//id for threadjoin
	t_ullong		time_last_eat;
	t_ullong		time_wait;		//start delay for odd numbered threads
	int				num_eat;		//countdown to 0 in case inputed
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

/**
 * @brief Checks if inputs are within positive int range and converts to int 
 * (modified atoi)
 * 
 * @param argv input char* to convert and check
 * @return int atoi result if valid, -1 if not int or -ve or out of int range
 */
int			is_int(char *argv);

/**
 * @brief Parses inputs, calls is_int to filter and check, and stocks the 
 * resulting values in the appropriate int variable in the main struct
 * 
 * @param argc number of inputs
 * @param argv inputs as char*
 * @param main pointer to main struct to stock ints
 * @return int returns 1 if number of philosophers is less than 1, or an input
 * is invalid, 0 otherwise
 */
int			check_inputs(int argc, char **argv, t_main *main);

/**
 * @brief Utility to print error message in case of invalid input syntax
 * 
 * @return int returns 1 to pass to main return value
 */
int			invalid_input(void);

/* ************************************************************************** */
/* inits                                                                      */
/* ************************************************************************** */

/**
 * @brief make phil threads + monitoring thread
 * create threads to run the thread functions
 * join the threads to wait for termination before returning main
 * destroy the mutexes
 * @param main pointer main structure
 * @param phils pointer to first of t_phil array
 * @return int returns 1 in case of a pthread create or join fail, 0 otherwise
 */
int			init_threads(t_main *main, t_phil *phils);

/**
 * @brief initialise the t_phil array of structs
 * 
 * @param main pointer main structure
 * @param phils pointer to first of t_phil array
 * @return t_phil* pointer to first of t_phil array, or NULL if ENOMEM
 */
t_phil		*init_phils(t_main *main, t_phil *phils);

/**
 * @brief initialise the t_main struct
 * 
 * @param main pointer main structure
 * @param phils pointer to first of t_phil array
 * @return int 1 in case of mutex_init failure, 0 otherwise
 */
int			init_main(t_main *main, t_phil *phils);

/**
 * @brief Initialise the philosopher's left and right fork pointers to point
 * to the corresponding mutex in the main->forks array
 * 
 * @param main pointer main structure
 * @param phils pointer to first of t_phil array
 * @return int 0
 */
int			point_forks(t_main *main, t_phil *phils);

/* ************************************************************************** */
/* utils                                                                      */
/* ************************************************************************** */

/**
 * @brief initialises the start time of the program so that further timestamps
 * can be calculated relative to this point. Stocked in main->start_time
 * 
 * @param main pointer main structure for main->start_time
 * @return int -1 if failure in elapsed_time() : gettimeofday, 0 otherwise
 */
int			start_time(t_main *main);

/**
 * @brief calculates the time elapsed (in ms) since the start of the program 
 * (main->start_time)
 * 
 * @param main pointer main structure for main->start_time (initialised to 0)
 * @return t_ullong time elapsed in ms
 */
t_ullong	elapsed_time(t_main *main);

/**
 * @brief variadic free to free n number of pointers
 * 
 * @param n number to free
 * @param ... list of pointers to free
 */
void		ft_free(size_t n, ...);

/* ************************************************************************** */
/* locks                                                                      */
/* ************************************************************************** */

/**
 * @brief To print the required messages with the correct syntax without mixing
 * due to parrallel threads.
 * 
 * @param main pointer to main to access mutex
 * @param phil phil->id to identify the philosopher or 0 if nothing
 * @param message message to print
 */
void		print_lock(t_main *main, int phil, char *message);

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
int			phil_dead_lock(t_main *main, int mod);

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
int			num_eat_lock(t_main *main, t_phil *phil, int mod);

t_ullong	time_last_eat_lock(t_main *main, t_phil *phil, int mod);

/**
 * @brief 	grab both forks
	change time last eat to now
	useleep eat time
	decrement num_eat
	let go of forks
 * @param phil philospher structure
 */
void		eat_lock(t_phil *phil);

/* ************************************************************************** */
/* monitor                                                                    */
/* ************************************************************************** */

/**
 * @brief Monitors the philosophers to indicate when one has died.
 * Checks the time since last start of meal (time_last_eat) of each philosopher
 * against current time, if the time_death is exceeded, the philosopher is 
 * pronounced dead, and the flag main->phil_dead is set to 1 to signal all
 * other philosopher threads to end.
 * 
 * @param main pointer to main struct
 * @return int 0 if program should continue, 1 in case of death
 */
// static int	_check_death(t_main *main);

/**
 * @brief Monitors the number of times each philosopher has left to eat (if set
 * as input parameter)
 * If the num_eat of every philosopher is 0 then returns 1 to end program.
 * @param main pointer to main struct
 * @return int 0 if eating should continue, 1 when all meals are completed.
 */
// static int	_check_num_eat(t_main *main);

/**
 * @brief monitors the state of philosopher threads : loops while phil_dead 
 * stays 0, checks for death in phils, breaks in case of death
 * 
 * @param data pointer to main struct
 * @return void* pointer to main struct
 */
void		*ft_monitor(void *data);

/* ************************************************************************** */
/* philo (main)                                                               */
/* ************************************************************************** */

/**
 * @brief runs philo thread function.
 * Even numbered philos wait half the eat time before trying to grab a fork 
 * to avoid deadlocks
 * The main->phil_dead variable is checked at each step to interrupt the thread
 * if any of the philosophers die
 * The phil->eat_num variable is checked to make sure the philosopher has not
 * eaten all of their meals already.
 * After eating, the philosopher sleeps, then is listed as 'thinking' until 
 * they start the eating cycle again (or not).
 * @param data pointer to phil[i] struct for each philosopher
 * @return void* pointer to phil[i] struct for each philosopher
 */
void		*ft_philo(void *data);

/**
 * @brief Cleanup function : destroys mutexes, frees mallocs (phil struct array
 * + fork array)
 * 
 * @param main pointer to main struct
 * @param phils phil->id to print, 0 if none
 * @param message message to be printed to output
 * @param ret_val return value wanted
 * @return int ret_val (return value wanted)
 */
int			ft_clean(t_main *main, t_phil *phils, char *message, int ret_val);

/**
 * @brief philosopher program :
 * • One or more philosophers sit at a round table.
 * There is a large bowl of spaghetti in the middle of the table.
 * • The philosophers alternatively eat, think, or sleep.
 * While they are eating, they are not thinking nor sleeping;
 * while thinking, they are not eating nor sleeping;
 * and, of course, while sleeping, they are not eating nor thinking.
 * • There are also forks on the table. There are as many forks as philosophers.
 * • Because serving and eating spaghetti with only one fork is very 
 * inconvenient, a philosopher takes their right and their left forks to eat, 
 * one in each hand.
 * • When a philosopher has finished eating, they put their forks back on the 
 * table and start sleeping. Once awake, they start thinking again. 
 * The simulation stops when a philosopher dies of starvation.
 * • Every philosopher needs to eat and should never starve.
 * • Philosophers don’t speak with each other.
 * @param argc 
 * @param argv 
 * @return int 1 in case of error (ENOMEM or input syntax error), 0 otherwise
 */
int			main(int argc, char **argv);

#endif