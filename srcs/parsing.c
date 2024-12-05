/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:34 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/12/05 13:58:44 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	args_check(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isalpha(av[i][j]))
			{
				printf("Error: Argument %d has invalid input\n", i);
				exit(1);
			}
			j++;
		}
	}
}

void	num_check(t_data *data)
{
	if (data->nb_philo > 200)
	{
		printf("Error: Number of philosophers must be less than 200\n");
		exit(1);
	}
	if (data->nb_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_sleep <= 0 || data->time_to_eat <= 0)
	{
		printf("Error: All arguments must be only positive numbers\n");
		exit(1);
	}
}

void	param_parse(t_data *data, char **av)
{
	args_check(av);
	another_check(av);
	data->nb_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]) * 1000;
	data->time_to_eat = ft_atol(av[3]) * 1000;
	data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		data->max_meals = ft_atol(av[5]);
	num_check(data);
}

static long	atol_norm(size_t results, long sign, const char *str, long *index)
{
	if (str[*index] == '+'
		&& (str[*index + 1] >= '0' && str[*index + 1] <= '9'))
		(*index)++;
	while (str[*index])
	{
		if (str[*index] >= '0' && str[*index] <= '9')
			results = (results * 10) + (str[*index] - '0');
		else
			break ;
		if ((results > 2147483647 && sign == 1)
			|| (results > 2147483648 && sign == -1))
			return (-1);
		(*index)++;
	}
	return (results * sign);
}

long	ft_atol(const char *str)
{
	long	index;
	long	results;
	long	sign;

	index = 0;
	results = 0;
	sign = 1;
	while (str[index] == ' ' || (str[index] >= '\t' && str[index] <= '\r'))
		index++;
	if (str[index] == '-' && (str[index + 1] >= '0' && str[index + 1] <= '9'))
	{
		sign *= -1;
		index++;
	}
	return (atol_norm(results, sign, str, &index));
}
