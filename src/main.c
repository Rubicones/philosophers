/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgizzard <dgizzard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:55:53 by dgizzard          #+#    #+#             */
/*   Updated: 2022/06/24 13:57:36 by dgizzard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

t_info	*init_info(int argc, char **argv)
{
	t_info			*info;

	info = malloc(sizeof(t_info) * 1);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[4]);
	else
		info->times_must_eat = -1;
	info->philos_count = ft_atoi(argv[0]);
	info->time_to_die = ft_atoi(argv[1]);
	info->time_to_eat = ft_atoi(argv[2]);
	info->time_to_sleep = ft_atoi(argv[3]);
	info->forks = init_forks(info->philos_count);
	info->philos = malloc(sizeof(t_philo *) * info->philos_count);
	info->stop_it = 0;
	pthread_mutex_init(&info->printf_mutex, NULL);
	pthread_mutex_init(&info->both_forks_lock, NULL);
	return (info);
}

void	free_info(t_info *info)
{
	pthread_mutex_destroy(&info->both_forks_lock);
	pthread_mutex_destroy(&info->printf_mutex);
	free_forks(info->forks, info->philos_count);
	free(info->threads);
	free(info->philos);
	free(info);
}

int	threads_init(t_info *info)
{
	int			i;
	t_philo		*philo;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * (info->philos_count));
	info->threads = threads;
	info->time_start = current_time_ms();
	i = 0;
	while (i < info->philos_count)
	{
		philo = init_philo(i, info);
		philo->info->philos[i] = philo;
		pthread_create(&threads[i], NULL, philosopher, (void *) philo);
		i++;
	}
	i = 0;
	while (i < info->philos_count)
	{
		pthread_detach(threads[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char	**argv)
{
	t_info		*info;

	if (!isvalid_inputs(argc - 1, argv + 1))
		return (0);
	info = init_info(argc, argv + 1);
	threads_init(info);
	if (checkdead(info))
	{
		free_all_philos(info->philos, info->philos_count);
		free_info(info);
		return (0);
	}
	return (0);
}
