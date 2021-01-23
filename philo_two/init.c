/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:16:08 by mcaptain          #+#    #+#             */
/*   Updated: 2021/01/23 22:20:22 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t	*open_semaphore(char *name, int num)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT, 0600, num));
}

int		init_semaphore(t_info *info)
{
	if ((info->forks = open_semaphore("FORKS", info->num)) == SEM_FAILED ||
			(info->print = open_semaphore("PRINT", 1)) == SEM_FAILED ||
			(info->dead = open_semaphore("DEAD", 0)) == SEM_FAILED)
		return (1);
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
