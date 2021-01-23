/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaptain <mcaptain@msk-school21.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 22:01:08 by mcaptain          #+#    #+#             */
/*   Updated: 2021/01/23 17:15:56 by mcaptain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

# define EAT 1
# define SLEEP 2
# define DEAD 3
# define THINK 4
# define L_FORK 5
# define R_FORK 6
# define ALL_EATING 7

struct s_philo;

typedef struct		s_info
{
	int				num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				stop;
	uint64_t		start_time;
	struct s_philo	*philos;
	sem_t			*forks;
	sem_t			*dead;
	sem_t			*print;
}					t_info;

typedef struct		s_philo
{
	int				id;
	int				is_eating;
	int				n_eat;
	int				l_fork;
	int				r_fork;
	uint64_t		last_eating;
	t_info			*info;
}					t_philo;

int					ft_atoi(const char *nptr);
uint64_t			get_time(void);
void				*counter(void *data);
void				*monitor(void *data);
void				*live(void *data);
void				print(t_philo *philo, int type);
int					init_semaphore(t_info *info);
int					init_philos(t_info *info);

#endif
