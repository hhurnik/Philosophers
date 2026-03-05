/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:32:30 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/23 17:32:30 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	extract_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = extract_time();
	while ((extract_time() - start) < milliseconds)
	{
		usleep(100);
	}
	return (0);
}

void	log_action(void *arg, const char *action)
{
	t_philo	*phil;
	int		should_print;

	phil = (t_philo *)arg;
	should_print = 0;
	pthread_mutex_lock(phil->sim_lock);
	if (*phil->simulation_running)
	{
		should_print = 1;
	}
	pthread_mutex_unlock(phil->sim_lock);
	if (should_print)
	{
		pthread_mutex_lock(phil->write_lock);
		printf("%ld %d %s\n", extract_time() - phil->start_time,
			phil->philosopher_number + 1, action);
		pthread_mutex_unlock(phil->write_lock);
	}
}
