/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcouchma <kcouchma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:37:09 by kcouchma          #+#    #+#             */
/*   Updated: 2024/04/11 19:01:20 by kcouchma         ###   ########.fr       */
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
	while (argv[i])
	{
		if (argv[i] > '9' || argv[i] < '0')
			return (-1);
		out *= 10;
		out += (argv[i] - '0');
		if (out > 2147483647)
			return (-1);
		i++;
	}
	return ((int)out);
}

int	check_inputs(int argc, char **argv, t_main *main)
{
	int	out;
	int	i;

	out = 0;
	i = 1;
	(void)argc;
	while (argv[i])
	{
		main->num_eat = -1;
		out = is_int(argv[i]);
		if (out == -1)
			return (1);
		else if (i == 1)
			main->num_phils = out;
		else if (i == 2)
			main->time_die = out;
		else if (i == 3)
			main->time_eat = out;
		else if (i == 4)
			main->time_sleep = out;
		else if (i == 5)
			main->num_eat = out;
		i++;
	}
	return (main->num_phils < 1);//not sure about this condition
}

int	invalid_input(void)
{
	printf("Invalid input, expected syntax is:\n./philo 1 2 3 4 5\n");
	printf("\t1 = # of philosophers (> 1)\n\t2 = time to die (ms)*\n");
	printf("\t3 = time to eat (ms)*\n\t4 = time to sleep (ms)*\n");
	printf("\t5 (optional) = # of eat cycles*\n"); //handle when 0
	printf("*values must be between 0 and 2,147,483,647\n");
	return (1);
}
