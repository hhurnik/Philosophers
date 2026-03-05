/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:52:04 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/24 16:52:17 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_continue(t_philo *phil)
{
	int	continue_sim;

	continue_sim = 1;
	pthread_mutex_lock(phil->sim_lock);
	if (!(*phil->simulation_running) || phil->has_died
		|| (phil->num_times_eat != -1
			&& phil->times_eaten >= phil->num_times_eat))
	{
		continue_sim = 0;
	}
	pthread_mutex_unlock(phil->sim_lock);
	return (continue_sim);
}

int	check_simulation_ended(t_philo *philo)
{
	if (!(*philo->simulation_running))
	{
		pthread_mutex_unlock(philo->sim_lock);
		return (1);
	}
	return (0);
}
