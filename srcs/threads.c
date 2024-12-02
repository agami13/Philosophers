/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:54:29 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/12/02 11:43:23 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	int	death_check(t_philo *philo)
{
	long	time_to_die;
	long	time;

	if (get_safe_flag(&philo->state_lock, &philo->flag))
		return (0);
	time = get_time() - get_safe_value(&philo->state_lock,
			&philo->last_meal);
	time_to_die = philo->data->time_to_die / 1000;
	if (time > time_to_die)
		return (1);
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!thread_active(&data->data_lock,
			&data->thread_active, data->nb_philo))
		;
	while (!simulation_end(data))
	{
		i = 0;
		while (i < data->nb_philo && !simulation_end(data))
		{
			if (death_check(&data->philos[i]))
			{
				update_value(&data->data_lock, &data->simulation_end, 1);
				print_state(&data->philos[i], DEAD);
			}
			i++;
		}
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!get_safe_flag(&philo->data->data_lock, &philo->data->thread_flag))
		;
	update_long_value(&philo->state_lock, &philo->last_meal, get_time());
	increment_value(&philo->data->data_lock,
		&philo->data->thread_active);
	if (!(philo->data->nb_philo % 2))
	{
		if (!(philo->pos % 2))
			ft_sleep(philo->data, 30000);
	}
	else if (philo->pos % 2)
		philo_think(philo, 1);
	while (!simulation_end(philo->data) && !get_safe_flag(&philo->data->data_lock,
			&philo->flag))
	{
		philo_eat(philo);
		print_state(philo, SLEEPING);
		ft_sleep(philo->data, philo->data->time_to_sleep);
		philo_think(philo, 0);
	}
	return (NULL);
}

int	simulation_start(t_data *data)
{
	int	i;

	i = 0;
	if (!data->max_meals)
		return (0);
	else if (data->nb_philo == 1)
	{
		if (pthread_create(&data->philos[0].thread, NULL, one_philo_routine, &data->philos[0])) 
			return (1);
	}
	else
	{
		while (i < data->nb_philo)
		{
			if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
				return (1);
			i++;
		}
	}
	if (pthread_create(&data->monitoring, NULL, monitoring, data))
		return (1);
	data->start_time = get_time();
	update_value(&data->data_lock, &data->thread_flag, 1);
	return (0);
}

int	exiting(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (1);
		i++;
	}
	update_value(&data->data_lock, &data->simulation_end, 1);
	if (pthread_join(data->monitoring, NULL))
		return (1);
	return (0);
}

// static void	exiting(t_data *data)
// {
// 	int	i;

// 	if (data->nb_philo == 1)
// 		pthread_detach(data->philos[0].thread);
// 	else
// 	{
// 		i = 0;
// 		while (i < data->nb_philo)
// 			pthread_join(data->philos[i++].thread, NULL);
// 	}
// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		pthread_mutex_destroy(&data->philos[i].state_lock);
// 		pthread_mutex_destroy(&data->forks[i]);
// 		i++;
// 	}
// 	pthread_mutex_destroy(&data->print);
// 	pthread_mutex_destroy(&data->meals);
// 	i = 0;
// 	while (i < data->nb_philo)
// 		free(data->philos[i++].id_char);
// 	free(data->philos);
// 	free(data->forks);
// }

// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;
// 	t_data	*data;

// 	philo = (t_philo *)arg;
// 	data = philo->data;
// 	if (philo->id % 2)
// 		usleep(1000);
// 	while (!simulation_end(data))
// 	{
// 		eating_state(philo);
// 		if (data->max_meals)
// 			break ;
// 		print_state(philo, "is sleeping", 1);
// 		ft_sleep(data, data->time_to_sleep);
// 		print_state(philo, "is thinking", 1);
// 	}
// 	return (NULL);
// }

// int	simulation_start(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->start_time = get_time();
// 	while (i < data->nb_philo)
// 	{
// 		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
// 				&data->philos[i]))
// 			return (1);
// 		data->philos[i].last_meal = get_time();
// 		i++;
// 	}
// 	check_death(data);
// 	pthread_mutex_unlock(&data->print);
// 	exiting(data);
// 	return (0);
// }
