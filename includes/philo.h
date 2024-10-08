/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:01:22 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/10/08 08:57:17 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
}					t_data;

int		ft_atoi(const char *str);
void	param_parse(t_data *data, char **av);
void	args_check(char **av);
int		ft_isalpha(int c);
void	num_check(t_data *data);

#endif