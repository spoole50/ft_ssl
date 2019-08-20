/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 13:19:00 by spoole            #+#    #+#             */
/*   Updated: 2019/08/12 13:19:34 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
#define FT_SSL_H

# include "libft/libft.h"
# include <stdint.h>
# include <sys/stat.h>

/*
** Algorithms
*/
# define MODE_NUM 2
# define MD5 0
# define SHA256 1
typedef char	*algorithm(unsigned char *message, int block_num);
char			*md5(unsigned char *message, int block_num);

# define false 0
# define true 1

/*
** Flags
*/
# define p_flag 0
# define q_flag 1
# define r_flag 2
# define s_flag 3

typedef struct			s_queue
{
	int					index;
	int					bit_size;
	int					is_file;
	int					block_num;
	char				*name;
	char				*result;
	struct s_queue		*next;
}						t_queue;

typedef struct 			s_ssl
{
	int					mode;
	int					flags;
	int					numQ;
	t_queue				*begin;
}						t_ssl;

/*
**	ft_ssl.h
**	Program Entry Point/Main Driver Functions
*/
void					err(t_queue *begin, char *err);
char					*check_stdin(int *size);
void					parse_flags(t_ssl *ssl, char *s1);
void					check_file(t_ssl *ssl, char *s1);
void					check_args(t_ssl *ssl, int ac, char **av);

/*
**	parse.c
**	Functions to assist in argument parsing
*/
void		parse_flags(t_ssl *ssl, char *s1);
void		check_file(t_ssl *ssl, char *s1);
int			get_mode(char *s1);
void		check_args(t_ssl *ssl, int ac, char **av);

/*
**	handle.c
**	Functions that handle argument initialization
*/
char		*check_stdin(int *size);
void		handle_s(t_ssl *ssl, char *s1, int is_arg);
void		handle_stdin(t_ssl *ssl);

/*
**	t_queue.c
**	t_queue structure management functions
*/

void					q_init(t_queue **begin, char *name, int size, int _is_file);
void					cleanQ(t_queue *begin);
void					printQ(t_queue *begin);

#endif
