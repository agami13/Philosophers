/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:24:23 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/11/20 13:53:55 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int    init_philo(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nb_philo)
    {
        data->philos[i].times_eaten = 0;
        data->philos[i].id = i + 1;
        data->philos[i].last_meal = 0;
        data->philos[i].data = data;
        data->philos[i].left_fork = i;
        data->philos[i].right_fork = (i + 1) % data->nb_philo;
    }
    if (i != data->nb_philo)

        return (1);
    return (0);
}

static int    init_mutex(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nb_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (1);
    }
    if (pthread_mutex_init(&data->print, NULL))
        return (1);
    if (pthread_mutex_init(&data->meals, NULL))
        return (1);
    return (0);
}

int    init(t_data *data)
{
    data->philos = malloc(sizeof(t_philo) * data->nb_philo);
    if (!data->philos)
        return (1);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if (!data->forks)
    {
        free(data->philos);
        return (1);
    }
    if (init_philo(data))
    {
        free(data->philos);
        free(data->forks);
        return (1);
    }
    if (init_mutex(data))
    {
        free(data->philos);
        free(data->forks);
        return (1);
    }
    return (0);
}
