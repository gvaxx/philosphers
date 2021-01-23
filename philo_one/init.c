/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:16:08 by mcaptain          #+#    #+#             */
/*   Updated: 2021/01/23 22:20:11 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_mutex(t_info *info)
{
	int	i;

	pthread_mutex_init(&info->dead, NULL);
	pthread_mutex_lock(&info->dead);
	pthread_mutex_init(&info->print, NULL);
	if (!(info->forks = malloc(sizeof(pthread_mutex_t) * info->num)))
		return (1);
	i = 0;
	while (i < info->num)
		pthread_mutex_init(&info->forks[i++], NULL);
	return (0);
}

int		init_philos(t_info *info)
{
	int	i;

	i = 0;
	if (!(info->philos = malloc(sizeof(t_philo) * info->num)))
		return (1);
	while (i < info->num)
	{
		info->philos[i].id = i;
		info->philos[i].is_eating = 0;
		info->philos[i].l_fork = i;
		info->philos[i].r_fork = (i + 1 == info->num) ? 0 : i + 1;
		info->philos[i].n_eat = 0;
		info->philos[i].info = info;
		i++;
	}
	return (0);
}
