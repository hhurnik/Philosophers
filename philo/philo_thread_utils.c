/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:12 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/23 17:28:12 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_monitor_thread(t_philo *philos)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, death_monitor, philos);
	pthread_join(monitor, NULL);
}

void	join_philo_threads(pthread_t *threads, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
