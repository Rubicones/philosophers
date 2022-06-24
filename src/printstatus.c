/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printstatus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgizzard <dgizzard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:56:21 by dgizzard          #+#    #+#             */
/*   Updated: 2022/06/24 13:56:21 by dgizzard         ###   ########.fr       */
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
