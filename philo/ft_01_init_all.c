/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_01_init_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:46:04 by inaranjo          #+#    #+#             */
/*   Updated: 2023/08/31 13:34:22 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*  allocation de mémoire pour les data du [philo]-[threads]-[mutex],
    selon le nombre de philos a table (all_philos)
    si les allocations echoue alors :
	il libere la memoire et return -1 en cas dechec*/
int	init_all(t_table *table)
{
	table->philo_routine = malloc(sizeof(t_data_philo) * table->all_philos);
	if (!table->philo_routine)
		return (free_all(table), -1);
	table->threads_id = malloc(sizeof(pthread_t) * table->all_philos);
	if (!table->threads_id)
		return (free_all(table), -1);
	if (init_mutex(table) == -1)
		return (-1);
	table->max_eat = 0;
	init_philo(table, table->philo_routine);
	init_threads(table);
	return (0);
}

/*init chaque philo[i] avec les varaiables de la struct t_data_philo
Si au moins deux philosophes sont présents,
chaque philosophe reçoit une fourchette à sa droite (table->forks). 
Si le nombre total de philosophes est inférieur ou égal à 1,
aucun fourchette n'est attribué, donc r_fork = NULL.*/
void	init_philo(t_table *table, t_data_philo *philo)
{
	int	i;

	i = -1;
	while (++i < table->all_philos)
	{
		philo[i].philo_id = i + 1;
		philo[i].start_time = &table->start_time;
		philo[i].l_fork = &table->forks[i];
		if (table->all_philos > 1)
			philo[i].r_fork = &table -> forks[(i + 1)
				% table->all_philos];
		else
			philo[i].r_fork = NULL;
		philo[i].total_eat_x_times = 0;
		philo[i].eat_x_times = table->eat_x_times;
		philo[i].last_meal = get_time();
		philo[i].stop = 0;
		philo[i].time_to_die = table->time_to_die;
		philo[i].time_to_eat = table->time_to_eat;
		philo[i].time_to_sleep = table->time_to_sleep;
		philo[i].max_eat = &table->max_eat;
		philo[i].padlock = &table->padlock;
		philo[i].private_fork = &table->private_fork[i];
		philo[i].display = &table->display;
	}
}

/*init les fourchettes + verrou privé de la struc t_table
 pour chaque "frouchette de dediées" aux philos a table"
  la fonction phtread_mutex_init permet d init les verrous
  un verrous et set de base sur ouvert*/
int	init_mutex(t_table *table)
{
	int		i;

	i = -1;
	table->forks = malloc(table->all_philos * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (free_all(table), -1);
	table->private_fork = malloc(table->all_philos * sizeof(pthread_mutex_t));
	if (!table->private_fork)
		return (free_all(table), -1);
	while (++i < table->all_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		pthread_mutex_init(&table->private_fork[i], NULL);
	}
	pthread_mutex_init(&table->padlock, NULL);
	pthread_mutex_init(&table->display, NULL);
	return (0);
}

/*grace a pthread_create : 
 chaque philo se voit atribuer un thread avec l'id de ce dernier
  + l atributions des donnees de philo_routine.
*/
int	init_threads(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = get_time();
	while (++i < table->all_philos)
		pthread_create(&table->threads_id[i], NULL,
			&philo_routine, &table->philo_routine[i]);
	return (1);
}