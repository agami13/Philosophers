/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:50:14 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/12/06 13:10:15 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}

int	another_check(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
		while ((av[i][j] >= '0' && av[i][j] <= '9') && av[i][j])
			j++;
		while (av[i][j])
		{
			if (av[i][j] == '+' || av[i][j] == '-')
			{
				printf("Error: Argument %d has invalid input\n", i);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
