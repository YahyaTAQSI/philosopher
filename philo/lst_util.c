/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:27:23 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/03/01 14:13:03 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	mns;
	int	res;

	mns = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			mns = -mns;
		i++;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * mns);
}

void	ft_error(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	write(2, s, i);
}

t_list	*ft_lstnew(int content, t_all *all)
{
	t_list	*lp;

	lp = (t_list *)malloc(sizeof(t_list));
	if (!lp)
		return (ft_error("malloc error\n"), NULL);
	if (pthread_mutex_init(&lp->pmt, NULL))
		return (ft_error("pthread_mutex_init error\n"), NULL);
	if (pthread_mutex_init(&lp->lsattime, NULL))
		return (ft_error("pthread_mutex_init error\n"), NULL);
	if (pthread_mutex_init(&lp->nbeat, NULL))
		return (ft_error("pthread_mutex_init error\n"), NULL);
	lp->all = all;
	lp->id = content + 1;
	lp->cp = 0;
	lp->dead = 1;
	lp->state = 0;
	lp->next = lp;
	return (lp);
}

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nextlst;
	t_list	*head;

	if (!new)
		return (0);
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	head = *lst;
	nextlst = *lst;
	while (nextlst->next != head)
		nextlst = nextlst->next;
	nextlst->next = new;
	new->next = head;
	return (1);
}
