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

FILES = ft_ssl.c t_queue.c handle.c parse.c digest.c md5.c sha256.c message.c bit_ops.c sha512.c sha384.c sha224.c sha512_224.c sha512_256.c sha1.c
LIBFT = libft
LIBFTA = libft.a

INCL = includes
SRCS = srcs/*.c

all : $(NAME)

libft:
	@make -C $(LIBFT)

$(NAME): libft $(OBJS)
	@$(CC) $(CFLAGS) -I$(INCL) -I$(LIBFT) $(SRCS) $(LIBFT)/$(LIBFTA) -o $(NAME)

clean:
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME) $(NAME).dSYM
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all libft $(NAME) clean fclean re $(OBJS)