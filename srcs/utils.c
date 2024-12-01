/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:20:29 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/12/01 20:47:30 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static unsigned int	num_len(int num)
{
	unsigned int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len += 1;
	}
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	num;
	unsigned int	len;

	len = num_len(n);
	num = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	if (num == 0)
		str[0] = '0';
	str[len] = '\0';
	while (num != 0)
	{
		str[len - 1] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	return (str);
}

void	update_flag(pthread_mutex_t *mutex, long *update, long value)
{
	pthread_mutex_lock(mutex);
	*update = value;
	pthread_mutex_unlock(mutex);
}

int	get_safe_flag(pthread_mutex_t *mutex, int *flag)
{
	int ret;

	pthread_mutex_lock(mutex);
	ret = *flag;
	pthread_mutex_unlock(mutex);
	return (ret);
}

int	simulation_end(t_data *data)
{
	int	ret;

	ret = get_safe_flag(&data->data_lock, &data->simulation_end);
	return (ret);
}

// int	simulation_end(t_data *data)
// {
// 	int	ret;

// 	ret = 0;
// 	pthread_mutex_lock(&data->death);
// 	if (data->simulation_end)
// 		ret = 1;
// 	pthread_mutex_unlock(&data->death);
// 	return (ret);
// }