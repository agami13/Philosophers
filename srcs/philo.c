/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:36 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/10/08 09:03:02 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*thread1(void *arg)
{
	int i = -1;
	while (++i < 5)
		printf("iter[thread] : %d\n", i);
	return NULL;
}
void	main_thread(void)
{
	int i = -1;
	while (++i < 5)
		printf("iter[main] : %d\n", i);
}

int main(int argc, char *argv[])
{
	pthread_t	new;
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (argc >= 5 && argc <= 6)
	{
		param_parse(data, argv);
		pthread_create(&new, NULL, thread1, NULL);
		main_thread();
		pthread_join(new, NULL);
		printf("\n\n\n\n%s", argv[1]);
	}
	else
	{
		write(1, "number of arguments must be 4 or 5!\n", 37);
		return (1);
	}
	return (0);
}