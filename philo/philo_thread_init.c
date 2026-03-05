/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:08:33 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/24 17:18:35 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo_threads(pthread_t **threads, int num)
{
	pthread_t	*phil_threads;

	phil_threads = malloc(sizeof(pthread_t) * num);
	if (!phil_threads)
		return (1);
	*threads = phil_threads;
	return (0);
}

void	fill_philosophers(int num, char *argv[], long start_time,
		t_philo *philos)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philos[i].philosopher_number = i;
		philos[i].number_of_philosophers = num;
		philos[i].time_to_die = ft_atoi(argv[2]);
		philos[i].time_to_eat = ft_atoi(argv[3]);
		philos[i].time_to_sleep = ft_atoi(argv[4]);
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % num;
		philos[i].start_time = start_time;
		philos[i].last_meal_time = start_time;
		philos[i].times_eaten = 0;
		philos[i].has_died = 0;
		i++;
	}
}

int	create_philosophers(int num, pthread_mutex_t *sim_lock,
		pthread_mutex_t *forks, t_philo *philos)
{
	pthread_t	*phil_threads;
	int			ret;

	ret = init_philo_threads(&phil_threads, num);
	if (ret != 0)
		return (ret);
	ret = launch_philosophers(phil_threads, philos, sim_lock, forks);
	if (ret != 0)
		return (ret);
	launch_monitor_thread(philos);
	join_philo_threads(phil_threads, num);
	free(phil_threads);
	return (0);
}

int	launch_philosophers(pthread_t *threads, t_philo *philos,
		pthread_mutex_t *sim_lock, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philos->number_of_philosophers)
	{
		philos[i].sim_lock = sim_lock;
		philos[i].forks = forks;
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
		{
			free(threads);
			return (1);
		}
		i++;
	}
	return (0);
}
