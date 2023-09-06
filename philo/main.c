/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:47:18 by inaranjo          #+#    #+#             */
/*   Updated: 2023/08/29 22:17:27 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table *table;

   table = malloc(sizeof(t_table));
    if (!(ac >= 5 && ac <= 6))
        ft_error("Number of arguments invalid\n");
    else if( ac == 5 || ac == 6)
    {
        if(ft_parse_input(table,ac,av) == 0)
        {
            ft_error("Arguments are invalide\n");
			return (1);
        }
        if(init_all(table) == -1)
            return (1);
        control(table, table->philo_routine);
        wait_threads(table);
        destroy(table);
        free_all(table);  
    }
    return (0);
}


