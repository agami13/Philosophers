/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:24:07 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/12/02 11:23:59 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	data.max_meals = -1;
	data.simulation_end = 0;
	param_parse(&data, argv);
	if (init(&data))
		return (1);
	if (simulation_start(&data))
		return (1);
	if (exiting(&data))
		return (1);
	cleanup(&data);
	return (0);
}
