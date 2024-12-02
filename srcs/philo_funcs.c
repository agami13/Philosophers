/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:41:40 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/12/02 11:23:36 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_safe_flag(&philo->data->data_lock, &philo->data->thread_flag))
		;
	update_long_value(&philo->state_lock, &philo->last_meal, get_time());
	increment_value(&philo->data->data_lock, &philo->data->thread_active);
	print_state(philo, FORK1);
	while (!simulation_end(philo->data))
		usleep(100);
	return (NULL);
}

void	print_state(t_philo *philo, t_state state)
{
	if (get_safe_flag(&philo->state_lock, &philo->flag))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	if ((state == FORK1 || state == FORK2) && !(get_safe_flag(&philo->data->data_lock, &philo->data->simulation_end)))
		printf("%ld %d has taken a fork\n", get_time() - philo->data->start_time, philo->pos);
	else if (state == EATING && !(get_safe_flag(&philo->data->data_lock, &philo->data->simulation_end)))
		printf("%ld %d is eating\n", get_time() - philo->data->start_time, philo->pos);
	else if (state == SLEEPING && !(get_safe_flag(&philo->data->data_lock, &philo->data->simulation_end)))
		printf("%ld %d is sleeping\n", get_time() - philo->data->start_time, philo->pos);
	else if (state == THINKING && !(get_safe_flag(&philo->data->data_lock, &philo->data->simulation_end)))
		printf("%ld %d is thinking\n", get_time() - philo->data->start_time, philo->pos);
	else if (state == DEAD)
		printf("%ld %d died\n", get_time() - philo->data->start_time, philo->pos);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1_mutex);
	print_state(philo, FORK1);
	pthread_mutex_lock(philo->fork2_mutex);
	print_state(philo, FORK2);
	update_long_value(&philo->state_lock, &philo->last_meal, get_time());
	philo->meals_count++;
	print_state(philo, EATING);
	ft_sleep(philo->data, philo->data->time_to_eat);
	if (philo->data->max_meals != -1 && philo->meals_count == philo->data->max_meals)
		update_value(&philo->state_lock, &philo->flag, 1);
	pthread_mutex_unlock(philo->fork1_mutex);
	pthread_mutex_unlock(philo->fork2_mutex);
}

void	philo_think(t_philo *philo, int flag)
{
	long	time_to_sleep;
	long	time_to_eat;
	long	time_to_think;

	if (!flag)
		print_state(philo, THINKING);
	if (!(philo->data->nb_philo % 2))
		return ;
	time_to_sleep = philo->data->time_to_sleep;
	time_to_eat = philo->data->time_to_eat;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	ft_sleep(philo->data, time_to_think * 0.1);
}

// void	print_state(t_philo *philo, char *message, int state)
// {
// 	char	*time_in_ms;

// 	time_in_ms = ft_itoa(get_time() - philo->data->start_time);
// 	pthread_mutex_lock(&philo->data->print);
// 	if (!simulation_end(philo->data) && !philo->data->max_meals)
// 		printf("%s %s %s\n", time_in_ms, philo->id_char, message);
// 	if (state)
// 		pthread_mutex_unlock(&philo->data->print);
// 	free(time_in_ms);
// }

// void	eating_state(t_philo *philo)
// {
// 	t_data	*data;

// 	data = philo->data;
// 	pthread_mutex_lock(&data->forks[philo->left_fork]);
// 	print_state(philo, "has taken a fork", 1);
// 	pthread_mutex_lock(&data->forks[philo->right_fork]);
// 	print_state(philo, "has taken a fork", 1);
// 	pthread_mutex_lock(&data->meals);
// 	pthread_mutex_lock(&philo->state_lock);
// 	print_state(philo, "is eating", 1);
// 	philo->last_meal = get_time();
// 	pthread_mutex_unlock(&data->meals);
// 	ft_sleep(data, data->time_to_eat);
// 	philo->times_eaten++;
// 	pthread_mutex_unlock(&philo->state_lock);
// 	pthread_mutex_unlock(&data->forks[philo->right_fork]);
// 	pthread_mutex_unlock(&data->forks[philo->left_fork]);
// }

// static int	helper_func(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->nb_philo && data->meals_counter
// 			&& data->philos[i].times_eaten >= data->meals_counter)
// 		i++;
// 	if (i == data->nb_philo)
// 		data->max_meals = 1;
// 	if (data->max_meals)
// 		return (1);
// 	return (0);
// }

// int	did_Die(t_philo *philo, unsigned long time_to_die)
// {
// 	if (get_time() - philo->last_meal > time_to_die)
// 	{
// 		print_state(philo, "died", 0);
// 		pthread_mutex_lock(&philo->data->death);
// 		philo->data->simulation_end = 1;
// 		pthread_mutex_unlock(&philo->state_lock);
// 		pthread_mutex_unlock(&philo->data->death);
// 		return (1);
// 	}
// 	return (0);
// }

// void	check_death(t_data *data)
// {
// 	int	i;

// 	while (!data->max_meals)
// 	{
// 		i = 0;
// 		while (i < data->nb_philo)
// 		{
// 			pthread_mutex_lock(&data->philos[i].state_lock);
// 			if (did_Die(&data->philos[i], data->time_to_die))
// 				return ;
// 			pthread_mutex_unlock(&data->philos[i].state_lock);
// 			i++;
// 		}
// 		if (helper_func(data))
// 			break ;
// 	}
// }
