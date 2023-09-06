/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_00_input_pars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:12:26 by inaranjo          #+#    #+#             */
/*   Updated: 2023/08/31 13:22:41 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*is_digit : uniquement des chiffre sautorisés*/
int ft_only_nb(char  *av[])
{
	int	i;
	int j;

	i = 1;
	while(av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*init les variables pour le nombre de philo
  ainsi que les régles liée au temps en millisecondes des philo */
int ft_parse_input(t_table *table,int ac, char **av)
{
	if(ft_only_nb(av))
	{
        table->all_philos = ft_atoi(av[1]);
	    table->time_to_die = ft_atoi(av[2]);
	    table->time_to_eat = ft_atoi(av[3]);
	    table->time_to_sleep = ft_atoi(av[4]);
        table->eat_x_times = -1;
	    if (ac == 6)
		    table->eat_x_times = ft_atoi(av[5]);
        return(1);
	}
	return (0);
}