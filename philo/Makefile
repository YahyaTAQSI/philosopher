# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 14:24:45 by ytaqsi            #+#    #+#              #
#    Updated: 2023/02/28 19:06:08 by ytaqsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCMAN = philo.c \
		lst_util.c \
		parcing.c \
		utils.c \

CC = cc
CFLAGS = -Wall -Werror -Wextra
FRM = rm -rf

NAME = philo
HEADER = philo.h

all: $(NAME)

$(NAME): $(SRCMAN) $(HEADER)
	$(CC) $(CFLAGS) $(SRCMAN) -o $(NAME)

clean:
	$(FRM) $(NAME)

fclean: clean

re: fclean all
