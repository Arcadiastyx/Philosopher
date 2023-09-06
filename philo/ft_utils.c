/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:55:10 by inaranjo          #+#    #+#             */
/*   Updated: 2023/08/29 21:31:38 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	write(2, "error: ", 7);
	write(2, str, i);
}

int	ft_atoi(const char *str)
{
	long	resultat;
	int		i;
	int		sig;

	resultat = 0;
	i = 0;
	sig = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}		
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = (resultat * 10) + (str[i] - '0');
		i++;
	}
	return (resultat * sig);
}

void	free_all(t_table *table)
{
	if (table->threads_id)
		free(table->threads_id);
	if (table->forks)
		free(table->forks);
	if (table->philo_routine)
		free(table->philo_routine);
	if (table->private_fork)
		free(table->private_fork);
	if (table)
		free(table);
}

//print_info
void	print_action(t_data_philo *philo, char *action)
{
	long int	time;

	pthread_mutex_lock(philo->display);
	time = get_time() - *philo -> start_time;
	if (time >= 0 && time <= INT_MAX && is_alive(philo))
		printf("[%d] Philo: %d %s\n", (int)time, philo -> philo_id, action);
	pthread_mutex_unlock(philo->display);
}

void	destroy(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table -> all_philos)
	{
		pthread_mutex_destroy(&table -> forks[i]);
		pthread_mutex_destroy(&table -> private_fork[i]);
	}
	pthread_mutex_destroy(&table -> padlock);
	pthread_mutex_destroy(&table -> display);
}