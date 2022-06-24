/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstatus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejafer <ejafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:50:20 by ejafer            #+#    #+#             */
/*   Updated: 2022/03/30 20:01:47 by ejafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	printstatus(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->info->printf_mutex);
	printf("%lld %d %s\n",
		current_time_ms() - philo->info->time_start, philo->num, status);
	pthread_mutex_unlock(&philo->info->printf_mutex);
}
