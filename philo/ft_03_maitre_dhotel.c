/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_03_maitre_dhotel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:09:07 by inaranjo          #+#    #+#             */
/*   Updated: 2023/08/31 16:42:18 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Vérifiez si tous les philosophes ont atteint le nombre max de repas
	Si c'est le cas,
	print action :indiquant que tous les repas ont été finis
	le flag stop a 1, indique qu'ils doivent s'arrêter.
*/
int	check_dining_status(t_table *table, t_data_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->padlock);
	if (table -> max_eat == table -> all_philos)
	{
		printf("%s\n", FINISH_MEAL);
		while (++i < table -> all_philos)
			philo[i].stop = 1;
		pthread_mutex_unlock(&table -> padlock);
		return (-1);
	}
	pthread_mutex_unlock(&table -> padlock);
	return (0);
}

/*
	Surveiller l'état des philo et apllque les conditions.
	Parcour les philo et vérifier si l'un d'entre eux a
	dépassé le délai de décès. 
	Si c'est le cas, afficher un message de décès et arrêter.
	Après avoir vérifié le délai de décès : 
	appeler check_dining_status pour vérifier si tous
    les repas ont été accomplis.
*/
void	control(t_table *table, t_data_philo *philo)
{
	int				i;

	i = -1;
	while (++i < table -> all_philos)
	{
		pthread_mutex_lock(&table -> private_fork[i]);
		if (get_time() - philo[i].last_meal >= table -> time_to_die)
		{
			pthread_mutex_unlock(&table -> private_fork[i]);
			pthread_mutex_lock(&table -> padlock);
			printf("[%d] Philo: %d %s\n", \
				(int)(get_time() - table -> start_time), i + 1, DIE);
			i = -1;
			while (++i < table -> all_philos)
				philo[i].stop = 1;
			pthread_mutex_unlock(&table -> padlock);
			return ;
		}
		pthread_mutex_unlock(&table -> private_fork[i]);
		if (check_dining_status(table, philo) == -1)
			return ;
		if (i + 1 == table -> all_philos)
			i = -1;
	}
}
