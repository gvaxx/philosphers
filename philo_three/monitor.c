/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:17:15 by mcaptain          #+#    #+#             */
/*   Updated: 2021/01/23 23:06:32 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*counter(void *data)
{
	int		i;
	int		all_feeding;
	t_info	*info;

	info = (t_info *)data;
	i = 0;

	while(i < info->num)
		sem_wait(info->philos[i++].eat);
	info->stop = 1;
	sem_post(info->dead);
	print(&info->philos[0], ALL_EATING);
	return (void *)0;
}

void	*monitor(void *data)
{
	int			i;
	t_philo		*philo;
	uint64_t	time;

	philo = (t_philo *)data;
	while (!philo->info->stop)
	{
		time = get_time() - philo->last_eating;
		if (!philo->is_eating &&
		((time) > philo->info->t_die))
		{
			philo->info->stop = 1;
			sem_post(philo->info->dead);
			print(philo, DEAD);
			return (void *)0;
		}
		usleep(10);
	}
	return (void *)0;
}
