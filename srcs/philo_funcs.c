/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:30:59 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/20 12:48:08 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_philo *philo, char *msg, int state)
{
	char	*time_in_ms;

	time_in_ms = ft_itoa(get_time() - philo->data->start_time);
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->simulation_end && !philo->data->max_meals)
		printf("%s %s %s\n", time_in_ms, ft_itoa(philo->id), msg);
	if (state != 0)
		pthread_mutex_unlock(&philo->data->print);
	free(time_in_ms);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	philo->state = EATING;
	print_state(philo, "has taken a fork", EATING);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_state(philo, "has taken a fork", EATING);
	pthread_mutex_lock(&philo->data->meals);
	print_state(philo, "is eating", EATING);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meals);
	ft_sleep(philo->data, philo->data->time_to_eat);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	check_death(t_data *data)
{
    unsigned int    current_time;
    int             i;

    current_time = get_time();
    i = 0;
    while (i < data->nb_philo && !data->simulation_end)
    {
        pthread_mutex_lock(&data->meals);
        if (current_time > data->philos[i].last_meal + data->time_to_die)
        {
            print_state(&data->philos[i], "died", DEAD);
            data->simulation_end = 1;
        }
        pthread_mutex_unlock(&data->meals);
		i++;
    }
}

void	check_maxMeals(t_data *data)
{
	int	i;

	if (data->max_meals > 0)
	{
		i = 0;
		while(i < data->nb_philo)
		{
			if (data->philos[i].times_eaten < data->max_meals)
				break ;
			i++;
		}
		if (i == data->nb_philo)
			data->simulation_end = 1;
	}
}

int simulation_end(t_data *data)
{
	while (!data->simulation_end)
	{
		check_death(data);
		if (data->simulation_end)
			return (1);
		check_maxMeals(data);
		if (data->simulation_end)
			return (1);
	}
	return (0);
}
