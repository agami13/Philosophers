/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:36:01 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/20 14:00:41 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 && data->nb_philo != 1)
		ft_sleep(data, data->time_to_eat / 50);
	while (!data->simulation_end && !data->max_meals)
	{
		philo_eat(philo);
		print_state(philo, "is sleeping", SLEEPING);
		ft_sleep(data, data->time_to_sleep);
		print_state(philo, "is thinking", THINKING);
	}
	return (NULL);
}

void	exiting_threads(t_data *data)
{
	int	i;

	if (data->nb_philo == 1)
		pthread_detach(data->philos[0].thread);
	else
	{
		i = -1;
		while (++i < data->nb_philo)
			pthread_join(data->philos[i].thread, NULL);
	}
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meals);
	free(data->philos);
	free(data->forks);
	free(data);
}

int	threads_begin(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, (void *)philo_routine, &data->philos[i]))
		{
			write(1, "Error: pthread_create\n", 23);
			return (1);
		}
		i++;
	}
	simulation_end(data);
	pthread_mutex_unlock(&data->print);
	exiting_threads(data);
	return (0);
}
