/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:00:17 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/24 15:43:32 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(t_data *data, unsigned long sleep_time)
{
	unsigned long	time_to_wakeup;

	time_to_wakeup = get_time() + sleep_time;
	while (get_time() < time_to_wakeup)
	{
		if (simulation_end(data))
			break ;
		usleep(1000);
	}
}
