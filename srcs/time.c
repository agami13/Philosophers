/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:00:17 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/24 14:50:27 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (unsigned long)1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(t_data *data, unsigned long sleep_time)
{
	unsigned long	time_to_wakeup;

	time_to_wakeup = get_time();
	while (!simulation_end(data))
	{
		if (get_time() - time_to_wakeup >= sleep_time)
			break ;
		usleep(data->nb_philo * 2);
	}
}

int	simulation_end(t_data *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->death);
	if (data->simulation_end)
		ret = 1;
	pthread_mutex_unlock(&data->death);
	return (ret);
}
