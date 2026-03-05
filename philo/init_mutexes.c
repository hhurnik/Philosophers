/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:18:50 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/24 17:18:50 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_resources(int num, t_philo **philos, pthread_mutex_t **forks)
{
	*philos = malloc(sizeof(t_philo) * num);
	*forks = malloc(sizeof(pthread_mutex_t) * num);
	if (!*philos || !*forks)
	{
		free(*philos);
		free(*forks);
		return (1);
	}
	return (0);
}

void	init_write_lock(t_philo *philos, pthread_mutex_t *write_lock, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philos[i].write_lock = write_lock;
		i++;
	}
}
