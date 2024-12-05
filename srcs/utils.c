/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:20:29 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/12/05 13:49:26 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	update_long_value(pthread_mutex_t *mutex, long *update, long value)
{
	pthread_mutex_lock(mutex);
	*update = value;
	pthread_mutex_unlock(mutex);
}

void	update_value(pthread_mutex_t *mutex, int *update, int value)
{
	pthread_mutex_lock(mutex);
	*update = value;
	pthread_mutex_unlock(mutex);
}

int	get_safe_flag(pthread_mutex_t *mutex, int *flag)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *flag;
	pthread_mutex_unlock(mutex);
	return (ret);
}

int	simulation_end(t_data *data)
{
	int	ret;

	ret = get_safe_flag(&data->data_lock, &data->simulation_end);
	return (ret);
}

void	cleanup(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo = &data->philos[i];
		pthread_mutex_destroy(&philo->state_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->data_lock);
	free(data->philos);
	free(data->forks);
}
