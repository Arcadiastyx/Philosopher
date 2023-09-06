/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_request.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:30:22 by inaranjo          #+#    #+#             */
/*   Updated: 2023/08/29 18:31:47 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*grace a gettimeofday : 
on peut obtenir l heure actuel en ms*/
long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*crée une attente pendant un certain nombre de ms
 en utilisant un horodatage*/
void	ft_usleep(int mil_sec)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < mil_sec)
		usleep(100);
}

/* attend que tous les threads et finis leur executions*/
int	wait_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table -> all_philos)
		pthread_join(table -> threads_id[i], NULL);
	return (1);
}