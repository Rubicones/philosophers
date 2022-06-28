/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgizzard <dgizzard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:56:04 by dgizzard          #+#    #+#             */
/*   Updated: 2022/06/24 13:57:46 by dgizzard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

t_philo	*init_philo(int n, t_info *info)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo) * 1);
	philo->num = n + 1;
	philo->info = info;
	philo->times_must_eat = philo->info->times_must_eat;
	philo->right = n;
	philo->left = n + 1;
	if (philo->left == philo->info->philos_count)
		philo->left = 0;
	return (philo);
}

void	free_philo(t_philo *philo)
{
	pthread_mutex_unlock(&philo->time_last_meal_lock);
	pthread_mutex_destroy(&philo->time_last_meal_lock);
	free(philo);
}

void	free_all_philos(t_philo **philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free_philo(philos[i]);
		i++;
	}
}
