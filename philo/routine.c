/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:26 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/23 17:28:26 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Function to handle single philosopher case */
void	handle_single_philo(t_philo *phil, int left_fork)
{
	pthread_mutex_lock(&phil->forks[left_fork]);
	log_action(phil, "has taken a fork");
	ft_usleep(phil->time_to_die);
	pthread_mutex_unlock(&phil->forks[left_fork]);
}

void	acquire_forks(t_philo *phil, int left_fork, int right_fork)
{
	if (phil->philosopher_number % 2 == 0)
	{
		pthread_mutex_lock(&phil->forks[left_fork]);
		log_action(phil, "has taken a fork");
		pthread_mutex_lock(&phil->forks[right_fork]);
		log_action(phil, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&phil->forks[right_fork]);
		log_action(phil, "has taken a fork");
		pthread_mutex_lock(&phil->forks[left_fork]);
		log_action(phil, "has taken a fork");
	}
}

// /* Function to handle eating phase */
int	handle_eating(t_philo *phil)
{
	int	finished;

	pthread_mutex_lock(phil->sim_lock);
	phil->last_meal_time = extract_time();
	pthread_mutex_unlock(phil->sim_lock);
	log_action(phil, "is eating");
	ft_usleep(phil->time_to_eat);
	pthread_mutex_lock(phil->sim_lock);
	phil->times_eaten++;
	finished = (phil->num_times_eat != -1
			&& phil->times_eaten >= phil->num_times_eat);
	pthread_mutex_unlock(phil->sim_lock);
	return (finished);
}

// /* Function to handle sleeping and thinking phases */
void	handle_sleeping_thinking(t_philo *phil, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&phil->forks[right_fork]);
	pthread_mutex_unlock(&phil->forks[left_fork]);
	log_action(phil, "is sleeping");
	ft_usleep(phil->time_to_sleep);
	log_action(phil, "is thinking");
}

// /* Main philosopher thread function */
void	*philo_routine(void *arg)
{
	t_philo	*phil;
	int		left_fork;
	int		right_fork;
	int		finished_eating;

	phil = (t_philo *)arg;
	left_fork = phil->philosopher_number;
	right_fork = (phil->philosopher_number + 1) % phil->number_of_philosophers;
	log_action(phil, "is thinking");
	if (phil->philosopher_number % 2 != 0)
		ft_usleep(phil->time_to_eat / 1.5);
	while (should_continue(phil))
	{
		if (phil->number_of_philosophers == 1)
		{
			handle_single_philo(phil, left_fork);
			return (NULL);
		}
		acquire_forks(phil, left_fork, right_fork);
		finished_eating = handle_eating(phil);
		handle_sleeping_thinking(phil, left_fork, right_fork);
		if (finished_eating)
			break ;
	}
	return (NULL);
}
