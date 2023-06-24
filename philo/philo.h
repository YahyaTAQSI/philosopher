/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:49:13 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/03/04 10:49:10 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_list
{
	int				id;
	size_t			cp;
	size_t			lt;
	struct s_list	*next;
	pthread_t		pt;
	pthread_mutex_t	pmt;
	pthread_mutex_t	lsattime;
	pthread_mutex_t	nbeat;
	int				state;
	struct s_all	*all;
	int				dead;
}					t_list;

typedef struct s_all
{
	t_list			*head;
	t_list			*phead;
	pthread_mutex_t	prnt;
	pthread_mutex_t	det;
	pthread_mutex_t	freall;
	size_t			st;
	int				nb;
	int				state;
	size_t			tdie;
	size_t			teat;
	size_t			tsleep;
	size_t			tmeat;
	int				alleat;
}					t_all;

int		ft_atoi(const char *str);
void	ft_error(char *s);
t_list	*ft_lstnew(int content, t_all *all);
int		ft_lstadd_back(t_list **lst, t_list *new);
int		ft_parcing(int ac, char **av, t_all *all);
void	*test(void *arg);
void	death(t_all *lst);
void	ft_prints(t_list *t, char *s);
size_t	get_time(void);
void	freestr(char **str);
void	destroyall(t_all *all);
int		ft_isdigit(int c);
void	ft_sleep(size_t t);

#endif
