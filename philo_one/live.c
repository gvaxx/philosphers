/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:13:16 by mcaptain          #+#    #+#             */
/*   Updated: 2021/01/23 19:47:50 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(int msec)
{
	long start;

	start = get_time();
	while (get_time() - start < msec)
		usleep(100);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
	print(philo, L_FORK);
	pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
	print(philo, R_FORK);
}

void	eat(t_philo *philo)
{
	philo->last_eating = get_time();
	philo->is_eating = 1;
	sleeping(philo->info->t_eat);
	philo->n_eat++;
	philo->is_eating = 0;
}

void	give_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
}

void	*live(void *data)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)data;
	philo->last_eating = get_time();
	while (!philo->info->stop)
	{
		take_forks(philo);
		print(philo, EAT);
		eat(philo);
		give_forks(philo);
		print(philo, SLEEP);
		sleeping(philo->info->t_sleep);
		print(philo, THINK);
	}
	return ((void *)0);
}
