/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:41 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/23 17:28:41 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_meal_goal(int num, int goal, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philos[i].num_times_eat = goal;
		i++;
	}
}

t_sim	init_simulation_data(int argc, char *argv[])
{
	t_sim	data;

	data.num = ft_atoi(argv[1]);
	if (argc == 6)
		data.meals = ft_atoi(argv[5]);
	else
		data.meals = -1;
	data.start_time = extract_time();
	return (data);
}

/* Modified setup_simulation to include forks initialization */
int	setup_simulation(t_sim *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num);
	if (!data->philos || !data->forks)
	{
		free(data->philos);
		free(data->forks);
		return (1);
	}
	while (i < data->num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_lock, NULL);
	return (0);
}

void	assign_sim_control(int num, int *sim_running, pthread_mutex_t *sim_lock,
		t_philo *philos)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philos[i].simulation_running = sim_running;
		philos[i].sim_lock = sim_lock;
		i++;
	}
}

void	cleanup_sim(t_sim *sim_data)
{
	int	i;

	i = 0;
	while (i < sim_data->num)
	{
		pthread_mutex_destroy(&sim_data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim_data->write_lock);
	pthread_mutex_destroy(&sim_data->sim_lock);
	free(sim_data->forks);
	free(sim_data->philos);
}
