/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhurnik <hhurnik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:19:08 by hhurnik           #+#    #+#             */
/*   Updated: 2025/04/24 17:19:08 by hhurnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s num_philos time_to_die time_to_eat"
			"time_to_sleep meals_needed\n", argv[0]);
		return (1);
	}
	if (!(is_pos_number(argv[1]) && is_pos_number(argv[2])
			&& is_pos_number(argv[3]) && is_pos_number(argv[4])))
	{
		printf("All arguments must be positive integers\n"
			"Usage: %s num_philos time_to_die time_to_eat"
			"time_to_sleep meals_needed\n", argv[0]);
		return (1);
	}
	if (argc == 6)
	{
		if (!is_pos_number(argv[5]))
		{
			printf("meals_needed must be positive integer\n"
				"Usage: %s num_philos time_to_die time_to_eat"
				"time_to_sleep meals_needed\n", argv[0]);
			return (1);
		}
	}
	return (0);
}

int	is_pos_number(char *s)
{
	if (!s || !*s)
		return (0);
	while (*s && (*s == 32 || (*s >= 9 && *s <= 13)))
		s++;
	if (*s == '0')
		return (0);
	if (*s == '+')
	{
		s++;
		if (*s == '0')
			return (0);
	}
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	numb;
	int	minus;

	minus = 1;
	numb = 0;
	while (*nptr && (*nptr == 32 || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	while (*nptr != '\0' && (*nptr >= '0' && *nptr <= '9'))
	{
		numb = numb * 10 + (*nptr - '0');
		nptr++;
	}
	return (minus * numb);
}
