/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:01:22 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/17 18:45:57 by ybouaoud         ###   ########.fr       */
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
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FORK = 4
}					t_state;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
}					t_data;

// routine functions

// time functions
time_t			get_time(void);
void			ft_sleep(t_data *data, time_t sleep_time);
void			delay(time_t delay_time);

// parsing functions
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
void	param_parse(t_data *data, char **av);
void	args_check(char **av);
void	num_check(t_data *data);

#endif