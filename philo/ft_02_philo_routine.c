/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_02_philo_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:13:34 by inaranjo          #+#    #+#             */
/*   Updated: 2023/08/31 14:58:08 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*grace au modulo on peut definir si un philo est pair ou impaire
	si == 0 alors c'est un philo paire.
l idee c est de determiner les impaires,si impaire alors 
il attend un instant avant de commencer a manger.
cela permet de décaler les début du repas entre philo impaire et pair.
  */
void	*philo_routine(void *arg)
{
	t_data_philo	*philo;

	philo = (t_data_philo *)arg;
	if (philo -> philo_id % 2 == 0)
		ft_usleep(philo->time_to_eat * 0.2);
	while (is_alive(philo))
	{
		if (dining_simulation(philo) == -1)
			return (NULL);
		if (!is_alive(philo))
			return (NULL);
		print_action(philo, SLEEP);
		ft_usleep(philo->time_to_sleep);
		print_action(philo, THINK);
	}
	return (NULL);
}

/*update_meal_status : 
-verrouille l acces a la fork,
-met a jour le time du dernier repas
-deverouille la fork
-verifie s il y une limite pour le nombre de repas, si oui
-alors le compteur et incrementer de 1 pour chauqe repas
-tout en respectant les mutex
*/
void	update_meal(t_data_philo *philo)
{
	pthread_mutex_lock(philo->private_fork);
	philo -> last_meal = get_time();
	pthread_mutex_unlock(philo->private_fork);
	if (philo -> eat_x_times != 0)
	{
		if (++philo->total_eat_x_times == philo -> eat_x_times)
		{
			pthread_mutex_lock(philo -> padlock);
			*philo->max_eat += 1;
			pthread_mutex_unlock(philo -> padlock);
		}
	}
}

/*simulation du repas : 
-vérifications pour s'assurer que le philosophe est en vie 
-à chaque étape de la simulation et utilise des verrous pour éviter les conflits.
-la fonction retourne 0 =succès et -1 = d'erreur ou 
	d'interruption due à la mort du philosophe.
*/
int	dining_simulation(t_data_philo	*philo)
{
	if (!is_alive(philo))
		return (-1);

	pthread_mutex_lock(philo->l_fork);
	print_action(philo, TAKE_L_FORK);

	if (!is_alive(philo))
		return (pthread_mutex_unlock(philo->l_fork), -1);

	if (philo->r_fork == NULL)
		return (pthread_mutex_unlock(philo -> l_fork),
			ft_usleep(philo -> time_to_die * 1), -1);// 1.1
        
	pthread_mutex_lock(philo->r_fork);
	print_action(philo, TAKE_R_FORK);
	print_action(philo, EAT);


	if (!is_alive(philo))
		return (pthread_mutex_unlock(philo->l_fork),
			pthread_mutex_unlock(philo->r_fork), -1);

	update_meal(philo);

	if (!is_alive(philo))
		return (pthread_mutex_unlock(philo -> l_fork),
			pthread_mutex_unlock(philo -> r_fork), -1);

	ft_usleep(philo->time_to_eat);
    
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (0);
}

/*verifie si le philo est en vie
 la fonction renvois 0 s il est en vie et 1 s il est mort*/
int	is_alive(t_data_philo *philo)
{
	pthread_mutex_lock(philo->padlock);
	if (!philo -> stop)
	{
		pthread_mutex_unlock(philo->padlock);
		return (1);
	}
	pthread_mutex_unlock(philo->padlock);
	return (0);
}