/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaranjo <inaranjo <inaranjo@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:47:51 by inaranjo          #+#    #+#             */
/*   Updated: 2023/08/31 15:08:50 by inaranjo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define EAT			("\033[1;32mis eating \033[0m")
# define SLEEP			("\033[1;33mis sleeping \033[0m")
# define THINK			("\033[1;36mis thinking \033[0m")
# define TAKE_L_FORK	("\033[1;38;2;255;165;0mhas taken left fork \033[0m")
# define TAKE_R_FORK	("\033[1;38;2;255;165;0mhas taken right fork \033[0m")
# define FINISH_MEAL	("\033[0;36m      --->Meal completed.d<---\033[0m")
# define DIE			("\033[1;91mdied \033[0m")

# define INT_MAX         2147483647


typedef struct s_data_philo
{
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_x_times;
	int				total_eat_x_times;
	int				*max_eat;
	long int		last_meal;
	long int		*start_time;
	int				stop;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*padlock;
	pthread_mutex_t	*private_fork;
	pthread_mutex_t	*display;
}				t_data_philo;


typedef struct s_table
{
	int				all_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_x_times;
	int				max_eat;
	pthread_t		*threads_id;
	t_data_philo	*philo_routine;
	pthread_mutex_t	*forks;
	pthread_mutex_t	display;
	long int		start_time;
	pthread_mutex_t	padlock;
	pthread_mutex_t	*private_fork;


}				t_table;

/*[00]input_parsing*/
int ft_only_nb(char  *av[]);
int ft_parse_input(t_table *table,int ac, char **av);

/*[01] initialisation des datas struct*/
int	init_all(t_table *table);
void	init_philo(t_table *table, t_data_philo *philo);
int	init_mutex(t_table *table);
int	init_threads(t_table *table);

/*[02] set the routine simulation*/
int	is_alive(t_data_philo *philo);
void	update_meal(t_data_philo *philo);
int	dining_simulation(t_data_philo	*philo);
void	*philo_routine(void *arg);

/*[03] superviseur afin de controler l etat des philo*/
int	check_dining_status(t_table *table, t_data_philo *philo);
void	control(t_table *table, t_data_philo *philo);

/*time request*/
long int	get_time(void);
void	    ft_usleep(int mil_sec);
int	        wait_threads(t_table *table);

/*utils*/
void	ft_error(char *str);
int     ft_atoi(const char *str);
void	free_all(t_table *table);
void	destroy(t_table *table);
void	print_action(t_data_philo *philo, char *action);


#endif
