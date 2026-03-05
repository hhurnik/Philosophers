/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:18:59 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/24 17:18:59 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_sim	sim_data;
	long	start_time;

	if (parse_input(argc, argv))
		return (1);
	sim_data = init_simulation_data(argc, argv);
	if (setup_simulation(&sim_data))
		return (1);
	start_time = extract_time();
	fill_philosophers(sim_data.num, argv, start_time, sim_data.philos);
	set_meal_goal(sim_data.num, sim_data.meals, sim_data.philos);
	init_write_lock(sim_data.philos, &sim_data.write_lock, sim_data.num);
	sim_data.sim_running = 1;
	pthread_mutex_init(&sim_data.sim_lock, NULL);
	assign_sim_control(sim_data.num, &sim_data.sim_running, &sim_data.sim_lock,
		sim_data.philos);
	create_philosophers(sim_data.num, &sim_data.sim_lock, sim_data.forks,
		sim_data.philos);
	cleanup_sim(&sim_data);
	return (0);
}
