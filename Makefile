# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spoole <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/12 13:17:47 by spoole            #+#    #+#              #
#    Updated: 2019/08/12 13:17:50 by spoole           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#REMOVE -g flag from ALL MAKE FILES

NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

FILES = ft_ssl.c t_queue.c handle.c parse.c md5.c
LIBFT = libft/

all : $(NAME)

libft:
	@make -C $(LIBFT) 

$(NAME): libft
	@$(CC) $(CFLAGS) $(FILES) -o $(NAME) $(LIBFT)/libft.a

clean:
	@rm -f *.o
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all libft $(NAME) clean fclean re