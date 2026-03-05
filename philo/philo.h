/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:06:26 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/24 17:20:10 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				philosopher_number;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_eat;

	int				left_fork;
	int				right_fork;

	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*forks;

	long			start_time;
	long			last_meal_time;
	int				times_eaten;
	int				has_died;

	int				*simulation_running;
	pthread_mutex_t	*sim_lock;
}					t_philo;

typedef struct s_sim
{
	int				num;
	int				meals;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	sim_lock;
	int				sim_running;
	long			start_time;
}					t_sim;

// monitor_death.c
int					check_philo_ate_enough(t_philo *philo);
int					check_all_ate_enough(t_philo *philos, int num,
						int *all_ate);
int					check_philo_death(t_philo *philo);
void				*death_monitor(void *arg);

// monitor_sumilation.c
int					should_continue(t_philo *phil);
int					check_simulation_ended(t_philo *philo);

// init_mutexes.c
int					init_resources(int num, t_philo **philos,
						pthread_mutex_t **forks);
void				init_write_lock(t_philo *philos,
						pthread_mutex_t *write_lock, int num);

// parsing.c
int					parse_input(int argc, char *argv[]);
int					is_pos_number(char *s);
int					ft_atoi(const char *nptr);

// philo_thread_init.c

int					init_philo_threads(pthread_t **threads, int num);
int					launch_philosophers(pthread_t *threads, t_philo *philos,
						pthread_mutex_t *sim_lock, pthread_mutex_t *forks);
int					create_philosophers(int num, pthread_mutex_t *sim_lock,
						pthread_mutex_t *forks, t_philo *philos);
void				fill_philosophers(int num, char *argv[], long start_time,
						t_philo *philos);

// philo_thread_utils.c
void				launch_monitor_thread(t_philo *philos);
void				join_philo_threads(pthread_t *threads, int num);

// routine.c
void				handle_single_philo(t_philo *phil, int left_fork);
void				acquire_forks(t_philo *phil, int left_fork, int right_fork);
int					handle_eating(t_philo *phil);
void				handle_sleeping_thinking(t_philo *phil, int left_fork,
						int right_fork);
void				*philo_routine(void *arg);

// sim_init_clean.c
void				set_meal_goal(int num, int goal, t_philo *philos);
t_sim				init_simulation_data(int argc, char *argv[]);
int					setup_simulation(t_sim *data);
void				assign_sim_control(int num, int *sim_running,
						pthread_mutex_t *sim_lock, t_philo *philos);
void				cleanup_sim(t_sim *sim_data);

// time.c
size_t				extract_time(void);
int					ft_usleep(size_t milliseconds);
void				log_action(void *arg, const char *action);

#endif
