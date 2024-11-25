/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:01:22 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/25 13:50:25 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

struct	s_data;

typedef struct s_philo
{
	int				times_eaten;
	int				id;
	char			*id_char;
	int				left_fork;
	int				right_fork;
	unsigned long	last_meal;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	eat_mutex;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				meals_counter;
	int				simulation_end;
	unsigned long	start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meals;
	pthread_mutex_t	death;
}					t_data;

// routine functions
void				check_death(t_data *data);
void				eating_state(t_philo *philo);
void				print_state(t_philo *philo, char *message, int state);
void				*philo_routine(void *arg);

// time functions
unsigned long		get_time(void);
void				ft_sleep(t_data *data, unsigned long sleep_time);

// init function
int					init(t_data *data);

// utils functions
char				*ft_itoa(int n);
int					simulation_end(t_data *data);
// unsigned long		get_last_meal(t_philo *philo);

// threads functions
int					simulation_start(t_data *data);

// parsing functions
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
void				param_parse(t_data *data, char **av);
void				args_check(char **av);
void				num_check(t_data *data);

#endif