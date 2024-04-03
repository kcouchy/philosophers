/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:37:09 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/03 12:10:42 by kcouchma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_int(char *argv)
{
	int		i;
	long	out;

	i = 0;
	out = 0;
	if (!argv[i])
		return (-1);
	while(argv[i])
	{
		if (argv[i] > '9' || argv[i] < '0')
			return(-1);
		out *= 10;
		out += (argv[i] - '0');
		if (out > 2147483647)
			return(-1);
		i++;
	}
	return ((int)out);
}

int	check_inputs(int argc, char **argv, t_philo *philo)
{
	int	out;
	int	i;

	out = 0;
	i = 1;
	(void)argc;
	while (argv[i])
	{
		out = is_int(argv[i]);
		if (out == -1)
			return (1);
		else if (i == 1)
			philo->num_phil = out;
		else if (i == 2)
			philo->time_die = out;
		else if (i == 3)
			philo->time_eat = out;
		else if (i == 4)
			philo->time_sleep = out;
		else if (i == 5)
			philo->num_eat = out;
		i++;
	}
	return (0);
}

void	invalid_input(void)
{
	printf("Invalid input, expected syntax is:\n./philo 1 2 3 4 5\n");
	printf("\t1 = # of philosophers\n\t2 = time to die (ms)\n");
	printf("\t3 = time to eat (ms)\n\t4 = time to sleep (ms)\n");
	printf("\t5 (optional) = # of eat cycles\n");
	printf("*all input values must be between 0 and 2,147,483,647\n");
}
