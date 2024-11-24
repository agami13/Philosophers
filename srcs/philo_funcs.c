/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:41:40 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/24 15:47:56 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_philo *philo, char *message, int state)
{
	char	*time_in_ms;

	time_in_ms = ft_itoa(get_time() - philo->data->start_time);
	pthread_mutex_lock(&philo->data->print);
	if (!simulation_end(philo->data) && !philo->data->max_meals)
		printf("%s %s %s\n", time_in_ms, philo->id_char, message);
	if (state)
		pthread_mutex_unlock(&philo->data->print);
	free(time_in_ms);
}

static void	try_to_aquire_fork(t_philo *philo, t_data *data)
{
	if (philo->id == data->nb_philo)
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_state(philo, "has taken a fork", 1);
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_state(philo, "has taken a fork", 1);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_state(philo, "has taken a fork", 1);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_state(philo, "has taken a fork", 1);
	}
}

void	eating_state(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	try_to_aquire_fork(philo, data);
	pthread_mutex_lock(&philo->data->meals);
	print_state(philo, "is eating", 1);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meals);
	ft_sleep(philo->data, philo->data->time_to_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

static int	helper_func(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->meals);
	while (i < data->nb_philo && data->meals_counter
		&& data->philos[i].times_eaten >= data->meals_counter)
		i++;
	if (i == data->nb_philo)
		data->max_meals = 1;
	pthread_mutex_unlock(&data->meals);
	if (data->max_meals)
		return (1);
	return (0);
}

void	check_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->meals);
			if ((int)(get_time()
				- data->philos[i].last_meal) >= data->time_to_die)
			{
				print_state(&data->philos[i], "died", 0);
				pthread_mutex_lock(&data->death);
				data->simulation_end = 1;
				pthread_mutex_unlock(&data->death);
				pthread_mutex_unlock(&data->meals);
				return ;
			}
			pthread_mutex_unlock(&data->meals);
			i++;
		}
		if (helper_func(data))
			break ;
	}
}
