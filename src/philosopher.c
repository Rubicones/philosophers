/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgizzard <dgizzard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:56:14 by dgizzard          #+#    #+#             */
/*   Updated: 2022/06/26 18:13:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_sleep(t_philo *philo)
{
	release_forks(philo);
	printstatus(philo, "is sleeping");
	philo_usleep(philo->info->time_to_sleep);
}

void	philo_think(t_philo	*philo)
{
	printstatus(philo, "is thinking");
	usleep(500);
}

int 	checkdead(void *info_t)
{	
	t_info		*info;
	int			i;

	info = (t_info *) info_t;
	while (1)
	{
		i = 0;
		while (i < info->philos_count)
		{
			if (info->stop_it == info->philos_count - 1)
				return (1);
			usleep(1000);
			pthread_mutex_lock(&info->philos[i]->time_last_meal_lock);
			if (current_time_ms() - info->philos[i]->time_last_meal
				>= info->time_to_die)
			{
				pthread_mutex_lock(&info->printf_mutex);
				printf("%lld %d died\n",
					   current_time_ms() - info->time_start, info->philos[i]->num);
				return (1);
			}
			pthread_mutex_unlock(&info->philos[i]->time_last_meal_lock);
			i++;
		}

	}
}

void	philo_eat(t_philo *philo)
{
	grab_forks(philo);
	pthread_mutex_lock(&philo->time_last_meal_lock);
	philo->time_last_meal = current_time_ms();
	pthread_mutex_unlock(&philo->time_last_meal_lock);
	printstatus(philo, "is eating");
	philo_usleep(philo->info->time_to_eat);
	if (philo->times_must_eat > 0)
		philo->times_must_eat--;
}

void	*philosopher(void *ptr_philo)
{
	t_philo			*philo;

	philo = (t_philo *) ptr_philo;
	pthread_mutex_init(&philo->time_last_meal_lock, NULL);
	philo->time_last_meal = current_time_ms();
	if (philo->num % 2 != 0)
		philo_usleep(philo->info->time_to_eat - 10);
	while (philo->times_must_eat)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	philo->info->stop_it++;
	return (NULL);
}
