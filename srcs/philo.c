/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:46:36 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/09/12 18:03:27 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		write(1, "number of arguments must be 4!\n", 32);
		return (1);
	}
	return (0);
}