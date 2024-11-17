/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:34 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/17 17:55:47 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	args_check(char **av)
{
	int i;
	int	j;
	i = 0;

	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isalpha(av[i][j]))
			{
				printf("Error: Argument %d is not a number\n", i);
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
		printf("Error: All arguments must be greater than 0\n");
		exit(1);
	}
}

void	param_parse(t_data *data, char **av)
{
	args_check(av);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -1;
	num_check(data);
}

int	ft_atoi(const char *str)
{
	long	index;
	long	results;
	int		sign;

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
	if (str[index] == '+' && (str[index + 1] >= '0' && str[index + 1] <= '9'))
		index++;
	while (str[index])
	{
		if (str[index] >= '0' && str[index] <= '9')
			results = (results * 10) + (str[index] - '0');
		else
			break ;
		index++;
	}
	return (results * sign);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z' ) || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}
