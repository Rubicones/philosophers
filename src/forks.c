/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:22:51 by ejafer            #+#    #+#             */
/*   Updated: 2022/06/23 16:35:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->both_forks_lock);
	pthread_mutex_lock(&philo->info->forks[philo->left]);
	pthread_mutex_lock(&philo->info->forks[philo->right]);
	pthread_mutex_unlock(&philo->info->both_forks_lock);
	printstatus(philo, "has taken a fork");
	printstatus(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->info->forks[philo->left]));
	pthread_mutex_unlock(&(philo->info->forks[philo->right]));
}

pthread_mutex_t	*init_forks(int count)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * (count));
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	free_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
}
