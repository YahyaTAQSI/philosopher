/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:47:41 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/03/01 14:11:18 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_allint(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_notinrange(char **s)
{
	int	i;
	int	nb;

	i = -1;
	while (s[++i])
	{
		nb = ft_atoi(s[i]);
		if ((i == 0 && (nb < 1 || nb > 200))
			|| (i && i < 4 && nb < 60) || (i == 4 && nb < 1))
			return (0);
	}
	return (1);
}

int	ft_init(char **av, t_all *all)
{
	all->tmeat = -1;
	all->alleat = 0;
	all->tdie = ft_atoi(av[2]);
	all->teat = ft_atoi(av[3]);
	all->tsleep = ft_atoi(av[4]);
	if (av[5])
		all->tmeat = ft_atoi(av[5]);
	all->head = NULL;
	all->nb = 0;
	while (all->nb < ft_atoi(av[1]))
	{
		if (!ft_lstadd_back(&all->head, ft_lstnew(all->nb++, all)))
			return (0);
	}
	all->phead = all->head;
	if (pthread_mutex_init(&all->prnt, NULL)
		|| pthread_mutex_init(&all->det, NULL)
		|| pthread_mutex_init(&all->freall, NULL))
		return (ft_error("pthread_mutex_init error\n"), 0);
	all->st = get_time();
	all->state = 0;
	return (1);
}

int	creatall(t_all *all)
{
	while (all->head)
	{
		if (!(all->head->id % 2))
			usleep(200);
		pthread_mutex_lock(&all->head->lsattime);
		all->head->lt = get_time();
		pthread_mutex_unlock(&all->head->lsattime);
		if (pthread_create(&all->head->pt, NULL, &test, all->head))
			return (ft_error("pthread_create error\n"), 1);
		pthread_detach(all->head->pt);
		all->head = all->head->next;
		if (all->head == all->phead)
			break ;
	}
	return (0);
}

int	ft_parcing(int ac, char **av, t_all *all)
{
	if (ac < 5 || ac > 6)
		return (ft_error("arguments error\n"), 1);
	if (!ft_allint(av + 1) || !ft_notinrange(av + 1))
		return (ft_error("int/arg error\n"), 1);
	if (!ft_init(av, all))
		return (1);
	if (creatall(all))
		return (destroyall(all), 1);
	death(all);
	destroyall(all);
	return (0);
}
