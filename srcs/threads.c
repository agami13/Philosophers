/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:54:29 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/23 14:12:10 by ybouaoud         ###   ########.fr       */
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
		pthread_mutex_destroy(&data->forks[i++]);
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
	int		i;
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	i = 0;
	if (philo->id % 2 && data->nb_philo > 1)
		ft_sleep(data, data->time_to_eat / 50);
	while (!data->simulation_end && !data->max_meals)
	{
		eating_state(philo);
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
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]))
			return (1);
		i++;
	}
	check_death(data);
	pthread_mutex_unlock(&data->print);
	exiting(data);
	return (0);
}
