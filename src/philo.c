/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:17:10 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/30 21:34:16 by ejafer           ###   ########.fr       */
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
	pthread_mutex_destroy(&philo->time_last_meal_lock);
	free(philo);
}

void	free_all_philos(t_philo **philos, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		pthread_mutex_destroy(&philos[i]->time_last_meal_lock);
		free(philos[i]);
	}
}
