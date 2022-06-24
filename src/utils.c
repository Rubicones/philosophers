/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgizzard <dgizzard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:56:28 by dgizzard          #+#    #+#             */
/*   Updated: 2022/06/24 13:56:29 by dgizzard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_usleep(long long ms)
{
	long long	start;
	long long	cur;

	start = current_time_ms();
	cur = current_time_ms();
	while (ms > cur - start)
	{
		usleep(1000);
		cur = current_time_ms();
	}
}

long long	current_time_ms(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

int	ft_atoi(const char *src)
{
	long long int	i;
	long long int	neg;
	long long int	r;

	r = 0;
	neg = 1;
	i = 0;
	while (src[i] == '\f' || src[i] == '\t' || src[i] == '\r' \
	|| src[i] == '\v' || src[i] == '\n' || src[i] == ' ')
		i++;
	if (src[i] == '+' || src[i] == '-')
	{
		if (src[i] == '-')
			neg *= -1;
		i++;
	}
	if (!(src[i] > 47 && src[i] < 58))
		return (0);
	while (src[i] > 47 && src[i] < 58)
		r = (src[i++] - '0') + (r * 10);
	if (r > 2147483648)
		return (-1);
	else if (r < -2147483647 - 1)
		return (0);
	return (neg * r);
}

int	ft_isdigit(int ch)
{
	if ((ch >= 48) && (ch <= 57))
		return (1);
	else
		return (0);
}

int	isvalid_inputs(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 4 && argc != 5)
		return (0);
	while (i < argc)
	{
		if (ft_isdigit(ft_atoi(argv[i]) == 0))
			return (0);
		i++;
	}
	return (1);
}
