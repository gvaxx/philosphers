/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:14:32 by mcaptain          #+#    #+#             */
/*   Updated: 2021/01/23 16:47:50 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_norminette(t_philo *philo, int type)
{
	if (type == EAT)
		printf("%09llu %i is eating\n",
			get_time() - philo->info->start_time, philo->id + 1);
	if (type == THINK)
		printf("%09llu %i think\n",
			get_time() - philo->info->start_time, philo->id + 1);
	if (type == R_FORK)
		printf("%09llu %i has taken a fork #%i\n",
			get_time() - philo->info->start_time,
			philo->id + 1, philo->r_fork + 1);
	if (type == L_FORK)
		printf("%09llu %i has taken a fork #%i\n",
			get_time() - philo->info->start_time,
			philo->id + 1, philo->l_fork + 1);
	if (type == SLEEP)
		printf("%09llu %i is sleeping\n",
			get_time() - philo->info->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->info->print);
}

void	print(t_philo *philo, int type)
{
	pthread_mutex_lock(&philo->info->print);
	if (type == DEAD)
	{
		printf("%09llu %i died\n",
			get_time() - philo->info->start_time, philo->id + 1);
		return ;
	}
	if (type == ALL_EATING)
	{
		printf("Everyone ate!\n");
		return ;
	}
	return (print_norminette(philo, type));
}
