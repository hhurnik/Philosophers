/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:49:18 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/24 16:49:18 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_ate_enough(t_philo *philo)
{
	if (philo->num_times_eat != -1
		&& philo->times_eaten >= philo->num_times_eat)
	{
		pthread_mutex_unlock(philo->sim_lock);
		return (1);
	}
	return (0);
}

int	check_all_ate_enough(t_philo *philos, int num, int *all_ate)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_lock(philos[i].sim_lock);
		if (check_simulation_ended(&philos[i]))
			return (1);
		if (check_philo_ate_enough(&philos[i]))
		{
			i++;
			continue ;
		}
		if (check_philo_death(&philos[i]))
			return (1);
		if (philos[i].num_times_eat != -1
			&& philos[i].times_eaten < philos[i].num_times_eat)
		{
			*all_ate = 0;
		}
		pthread_mutex_unlock(philos[i].sim_lock);
		i++;
	}
	return (0);
}

int	check_philo_death(t_philo *philo)
{
	long	now;
	long	time_since_last_meal;

	now = extract_time();
	time_since_last_meal = now - philo->last_meal_time;
	if (time_since_last_meal > philo->time_to_die && !philo->has_died)
	{
		philo->has_died = 1;
		pthread_mutex_unlock(philo->sim_lock);
		log_action(philo, "died");
		pthread_mutex_lock(philo->sim_lock);
		*philo->simulation_running = 0;
		pthread_mutex_unlock(philo->sim_lock);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_philo	*philos;
	int		num;
	int		all_ate;

	philos = (t_philo *)arg;
	num = philos[0].number_of_philosophers;
	while (1)
	{
		usleep(1000);
		all_ate = 1;
		if (check_all_ate_enough(philos, num, &all_ate))
			return (NULL);
		if (all_ate && philos[0].num_times_eat != -1)
		{
			pthread_mutex_lock(philos[0].sim_lock);
			*philos[0].simulation_running = 0;
			pthread_mutex_unlock(philos[0].sim_lock);
			return (NULL);
		}
	}
}
