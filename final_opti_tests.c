//gets rid of lock order warning by having last philo grab left fork first, but slows program sp death may occur
int	point_forks(t_main *main, t_phil *phils)
{
	int	i;

	i = 0;
	while (i < main->num_phils) //while (i < main->num_phils - 1)
	{
		phils[i].r_fork = &(main)->forks[i];
		if (i == 0)
			phils[i].l_fork = &(main)->forks[main->num_phils - 1];
		else
			phils[i].l_fork = &(main)->forks[i - 1];
		i++;
	}
	// if (i == main->num_phils - 1)
	// {
	// 	phils[i].r_fork = &(main)->forks[i - 1];
	// 	phils[i].l_fork = &(main)->forks[i];
	// }
	return (0);
}
