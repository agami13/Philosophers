/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:36 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/20 14:01:02 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char *argv[])
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (argc >= 5 && argc <= 6)
	{
		param_parse(data, argv);
		if (init(data))
		{
			write(1, "Error: init data failed failed!\n", 32);
			return (1);
		}
		if(threads_begin(data))
		{
			write(1, "Error: threads begin failed!\n", 30);
			return (1);
		}
		exiting_threads(data);
		free(data);
	}
	else
	{
		write(1, "number of arguments must be 4 or 5!\n", 37);
		return (1);
	}
	return (0);
}
