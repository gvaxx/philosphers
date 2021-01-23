/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:01:17 by mcaptain          #+#    #+#             */
/*   Updated: 2021/01/23 17:24:56 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		check_arg(t_info *info)
{
	if (info->num <= 0)
		return (1);
	if (info->t_eat <= 0)
		return (1);
	if (info->t_die <= 0)
		return (1);
	if (info->t_sleep <= 0)
		return (1);
	if (info->n_eat < 0)
		return (1);
	return (0);
}

int		parse_arg(int argc, char **argv, t_info *info)
{
	if (argc != 5 && argc != 6)
		return (1);
	info->num = ft_atoi(argv[1]);
	info->t_die = ft_atoi(argv[2]);
	info->t_eat = ft_atoi(argv[3]);
	info->t_sleep = ft_atoi(argv[4]);
	info->n_eat = argc == 6 ? ft_atoi(argv[5]) : 0;
	info->stop = 0;
	if (check_arg(info))
		return (1);
	return (0);
}

int		start_threads(t_info *info)
{
	pthread_t	t;
	int			i;

	i = 0;
	info->start_time = get_time();
	if (info->n_eat)
	{
		if (pthread_create(&t, NULL, &counter, (void *)info) != 0)
			return (1);
		pthread_detach(t);
	}
	while (i < info->num)
	{
		if (pthread_create(&t, NULL, &live, (void *)&info->philos[i++]) != 0)
			return (1);
		pthread_detach(t);
		usleep(1000);
	}
	pthread_create(&t, NULL, &monitor, (void *)info);
	pthread_detach(t);
	return (0);
}

int		clear(t_info *info)
{
	int	i;

	i = 0;
	usleep(1000 * info->num);
	free(info->philos);
	sem_unlink("FORKS");
	sem_unlink("DEAD");
	sem_unlink("PRINT");
	return (0);
}

int		main(int argc, char **argv)
{
	t_info	info;

	if (parse_arg(argc, argv, &info))
		return (1);
	if (init_semaphore(&info))
		return (1);
	if (init_philos(&info))
		return (1);
	start_threads(&info);
	sem_wait(info.dead);
	sem_post(info.dead);
	return (clear(&info));
}
