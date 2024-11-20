/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:36 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/20 09:56:51 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	*thread1(void *arg)
// {
// 	int i = -1;
// 	while (++i < 5)
// 		printf("iter[thread] : %d\n", i);
// 	return NULL;
// }
// void	main_thread(void)
// {
// 	int i = -1;
// 	while (++i < 5)
// 		printf("iter[main] : %d\n", i);
// }

int main(int argc, char *argv[])
{
	// pthread_t	new;
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (argc >= 5 && argc <= 6)
	{
		param_parse(data, argv);
		printf("nb_philo = %d\n", data->nb_philo);
		printf("time_to_die = %d\n", data->time_to_die);
		printf("time_to_eat = %d\n", data->time_to_eat);
		printf("time_to_sleep = %d\n", data->time_to_sleep);
		printf("max_meals = %d\n", data->max_meals);
	}
	else
	{
		write(1, "number of arguments must be 4 or 5!\n", 37);
		return (1);
	}
	return (0);
}