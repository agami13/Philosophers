/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:01:22 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/20 14:01:29 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum e_state
{
	DEAD = 0,
	EATING = 2,
	SLEEPING = 2,
	THINKING = 4
}					t_state;

struct s_data;

typedef	struct	s_philo
{
	int				times_eaten;
	int				id;
	int				left_fork;
	int				right_fork;
	unsigned int	last_meal;
	struct s_data	*data;
	t_state			state;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				simulation_end;
	unsigned int	start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meals;
}					t_data;

// routine functions
void			*philo_routine(void *arg);
void			print_state(t_philo *philo, char *msg, int state);
void			philo_eat(t_philo *philo);
void			check_death(t_data *data);
void			check_maxMeals(t_data *data);
int 			simulation_end(t_data *data);

// time functions
time_t			get_time(void);
void			ft_sleep(t_data *data, time_t sleep_time);
void			delay(time_t delay_time);

// init function
int				init(t_data *data);

// utils functions
char			*ft_itoa(int n);

// threads functions
int				threads_begin(t_data *data);
void			exiting_threads(t_data *data);

// parsing functions
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
void			param_parse(t_data *data, char **av);
void			args_check(char **av);
void			num_check(t_data *data);

#endif