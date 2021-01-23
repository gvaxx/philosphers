/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:17:15 by mcaptain          #+#    #+#             */
/*   Updated: 2021/01/23 17:18:17 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*counter(void *data)
{
	int		i;
	int		all_feeding;
	t_info	*info;

	info = (t_info *)data;
	all_feeding = 0;
	while (!all_feeding)
	{
		all_feeding = 1;
		i = 0;
		while (i < info->num)
		{
			if (info->n_eat > info->philos[i].n_eat)
				all_feeding = 0;
			i++;
		}
		usleep(10);
	}
	info->stop = 1;
	sem_post(info->dead);
	print(&info->philos[0], ALL_EATING);
	return (void *)0;
}

void	*monitor(void *data)
{
	int			i;
	t_info		*info;
	t_philo		*philo;
	uint64_t	time;

	info = (t_info *)data;
	while (!info->stop)
	{
		i = 0;
		while (i < info->num)
		{
			philo = &info->philos[i++];
			time = get_time() - philo->last_eating;
			if (!philo->is_eating &&
			((time) > info->t_die))
			{
				philo->info->stop = 1;
				sem_post(philo->info->dead);
				print(philo, DEAD);
				return (void *)0;
			}
			usleep(10);
		}
	}
	return (void *)0;
}
