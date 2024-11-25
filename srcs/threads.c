/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:54:29 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/25 13:26:42 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	exiting(t_data *data)
{
	int	i;

	if (data->nb_philo == 1)
		pthread_detach(data->philos[0].thread);
	else
	{
		i = 0;
		while (i < data->nb_philo)
			pthread_join(data->philos[i++].thread, NULL);
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philos[i].state_lock);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meals);
	i = 0;
	while (i < data->nb_philo)
		free(data->philos[i++].id_char);
	free(data->philos);
	free(data->forks);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(1000);
	while (!simulation_end(data))
	{
		eating_state(philo);
		if (data->max_meals)
			break ;
		print_state(philo, "is sleeping", 1);
		ft_sleep(data, data->time_to_sleep);
		print_state(philo, "is thinking", 1);
	}
	return (NULL);
}

int	simulation_start(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]))
			return (1);
		data->philos[i].last_meal = get_time();
		i++;
	}
	check_death(data);
	pthread_mutex_unlock(&data->print);
	exiting(data);
	return (0);
}
