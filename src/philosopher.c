/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                   ###   ########.fr       								  */
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

void	*checkdead(void *ptr_philo)
{	
	t_philo		*philo;
	t_info		*info;

	philo = (t_philo *) ptr_philo;
	while (philo->times_must_eat)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->time_last_meal_lock);
		if (current_time_ms() - philo->time_last_meal
			>= philo->info->time_to_die)
		{
			pthread_mutex_lock(&philo->info->printf_mutex);
			printf("%lld %d died\n",
				current_time_ms() - philo->info->time_start, philo->num);
			info = philo->info;
			free_all_philos(info->philos, info->philos_count);
			free_info(info);
			exit(0);
		}
		pthread_mutex_unlock(&philo->time_last_meal_lock);
	}
	return (NULL);
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
	pthread_t		death_check;

	philo = (t_philo *) ptr_philo;
	pthread_mutex_init(&philo->time_last_meal_lock, NULL);
	philo->time_last_meal = current_time_ms();
	pthread_create(&death_check, NULL, checkdead, (void *) philo);
	pthread_detach(death_check);
	if (philo->num - 1 % 2 != 0)
		philo_usleep(philo->info->time_to_eat - 10);
	while (philo->times_must_eat)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	free_philo(philo);
	return (NULL);
}
