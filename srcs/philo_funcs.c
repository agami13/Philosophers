/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:41:40 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/22 12:49:54 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_philo *philo, char *message, int state)
{
	char	*time_in_ms;

	time_in_ms = ft_itoa(get_time() - philo->data->start_time);
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->simulation_end && !philo->data->max_meals)
		printf("%s %s %s\n", time_in_ms, philo->id_char, message);
	if (state)
		pthread_mutex_unlock(&philo->data->print);
	free(time_in_ms);
}

void	eating_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_state(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_state(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->data->meals);
	print_state(philo, "is eating", 1);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meals);
	ft_sleep(philo->data, philo->data->time_to_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	check_death(t_data *data)
{
	int	i;

	while (!data->max_meals)
	{
		i = 0;
		while (i < data->nb_philo && !data->simulation_end)
		{
			pthread_mutex_lock(&data->meals);
			if ((int)(get_time()
				- data->philos[i].last_meal) >= data->time_to_die)
			{
				print_state(&data->philos[i], "died", 0);
				data->simulation_end = 1;
			}
			pthread_mutex_unlock(&data->meals);
			i++;
		}
		if (data->simulation_end)
			break ;
		i = 0;
		while (i < data->nb_philo && data->meals_counter
			&& data->philos[i].times_eaten >= data->meals_counter)
			i++;
		data->max_meals = (i == data->nb_philo);
	}
}
