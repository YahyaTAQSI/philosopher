/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:16:31 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/03/01 14:10:15 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_prints(t_list *t, char *s)
{
	size_t	time;

	pthread_mutex_lock(&t->all->prnt);
	time = (get_time() - t->all->st);
	printf("%zu %d %s\n", time, t->id, s);
	pthread_mutex_lock(&t->all->det);
	if (t->dead)
		pthread_mutex_unlock(&t->all->prnt);
	pthread_mutex_unlock(&t->all->det);
}

void	checkmeals(t_list *t, int *c)
{
	t_list	*curr;

	curr = t;
	*c = 0;
	while (t)
	{
		pthread_mutex_lock(&t->lsattime);
		if (t->cp == t->all->tmeat)
			(*c)++;
		pthread_mutex_unlock(&t->lsattime);
		t = t->next;
		if (t == curr)
			break ;
	}
}

void	death(t_all	*tmp)
{
	int	cp;

	while (1)
	{
		checkmeals(tmp->head, &cp);
		if (cp == tmp->nb)
		{
			pthread_mutex_lock(&tmp->det);
			tmp->head->dead = 0;
			pthread_mutex_unlock(&tmp->det);
			break ;
		}
		pthread_mutex_lock(&tmp->head->lsattime);
		if (get_time() - tmp->head->lt > tmp->tdie)
		{
			pthread_mutex_lock(&tmp->det);
			tmp->head->dead = 0;
			pthread_mutex_unlock(&tmp->det);
			ft_prints(tmp->head, "died");
			break ;
		}
		pthread_mutex_unlock(&tmp->head->lsattime);
		tmp->head = tmp->head->next;
	}
}

void	*test(void *arg)
{
	t_list	*tmp;

	tmp = (t_list *)arg;
	while (tmp->dead)
	{
		pthread_mutex_lock(&tmp->pmt);
		ft_prints(tmp, "has taken a fork");
		pthread_mutex_lock(&tmp->next->pmt);
		ft_prints(tmp, "has taken a fork");
		pthread_mutex_lock(&tmp->lsattime);
		tmp->lt = get_time();
		tmp->cp++;
		pthread_mutex_unlock(&tmp->lsattime);
		ft_prints(tmp, "is eating");
		ft_sleep(tmp->all->teat);
		pthread_mutex_unlock(&tmp->next->pmt);
		pthread_mutex_unlock(&tmp->pmt);
		ft_prints(tmp, "is sleeping");
		ft_sleep(tmp->all->tsleep);
		ft_prints(tmp, "is thinking");
	}
	pthread_mutex_unlock(&tmp->all->det);
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_all	all;

	ft_parcing(ac, av, &all);
	return (0);
}
