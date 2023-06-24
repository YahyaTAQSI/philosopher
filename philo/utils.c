/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:05:08 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/03/04 10:45:51 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + t.tv_usec / 1000);
}

void	freestr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	destroyall(t_all *all)
{
	t_list	*curr;
	int		i;

	i = -1;
	while (++i < all->nb)
	{
		pthread_mutex_lock(&all->freall);
		pthread_mutex_destroy(&all->head->pmt);
		pthread_mutex_destroy(&all->head->lsattime);
		pthread_mutex_destroy(&all->head->nbeat);
		curr = all->head;
		all->head = all->head->next;
		free(curr);
		pthread_mutex_unlock(&all->freall);
	}
	pthread_mutex_destroy(&all->prnt);
	pthread_mutex_destroy(&all->det);
	pthread_mutex_destroy(&all->freall);
}

void	ft_sleep(size_t t)
{
	size_t	ft;

	ft = get_time();
	while (get_time() < ft + t)
		usleep(100);
}
