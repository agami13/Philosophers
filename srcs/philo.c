/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:36 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/09/16 03:14:01 by ybouaoud         ###   ########.fr       */
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
	if (argc != 5)
	{
		write(1, "number of arguments must be 4!\n", 32);
		return (1);
	}
	pthread_create(&new, NULL, thread1, NULL);
	main_thread();
	pthread_join(new, NULL);
	printf("\n\n\n\n%s", argv[1]);
	return (0);
}