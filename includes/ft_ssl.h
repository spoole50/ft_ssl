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
# define FT_SSL_H

# include <libft.h>
# include <sys/stat.h>
# include <fcntl.h>

# define FALSE 0
# define TRUE 1

# define ROTL(x,n) ((x << (n % 32)) | (x >> ((32 - n) % 32)))
# define ROTR(x,n) ((x >> (n % 32)) | (x << ((32 - n) % 32)))

/*
** Flags
*/
# define P_FLAG 0
# define Q_FLAG 1
# define R_FLAG 2
# define S_FLAG 3
# define H_FLAG 4

/*
**	SSL Structs
*/
typedef struct			s_queue
{
	int					index;
	int					is_file;
	int					t_bytes;
	char				*name;
	char				*result;
	uint64_t			byte_size;
	struct s_queue		*next;
}						t_queue;

typedef struct			s_ssl
{
	int					mode;
	int					flags;
	int					num_q;
	t_queue				*begin;
}						t_ssl;

/*
** Algorithms
*/
# define MODE_NUM 8
# define MD5 0
# define SHA1 1
# define SHA224 2
# define SHA256 3
# define SHA384 4
# define SHA512 5
# define SHA512_224 6
# define SHA512_256 7

extern const char		*g_algos[MODE_NUM];

typedef char			*t_algorithm(unsigned char *message, t_queue *data);
char					*md5(unsigned char *message, t_queue *data);
char					*sha224(unsigned char *message, t_queue *data);
char					*sha256(unsigned char *message, t_queue *data);
char					*sha384(unsigned char *message, t_queue *data);
char					*sha512(unsigned char *message, t_queue *data);
char					*sha512_224(unsigned char *message, t_queue *data);
char					*sha512_256(unsigned char *message, t_queue *data);
char					*sha1(unsigned char *message, t_queue *data);

/*
**	ft_ssl.h
**	Program Entry Point/Main Driver Functions
*/
void					err(t_queue *begin, char *err);
void					print_help(t_queue *begin);

/*
**	bit_ops.c
**	Endian conversion swap functions
*/
uint32_t				swap_bits32(uint32_t x);
uint64_t				swap_bits64(uint64_t x);

/*
**	digest.c
**	Digest Operations
*/
void					make_result(unsigned char *output,\
						uint32_t *input, int len);
char					*str_result(unsigned char *output, int len);
void					digest(int mode, t_queue *data, int is_file);
void					process_message(t_ssl *ssl);

/*
**	message.c
**	Message Operations
*/
void					test_message(unsigned char *message, t_queue *data);
void					file_message(unsigned char *message, t_queue *data);
void					build_msg(unsigned char *formatted_msg,\
						t_queue *data, int is_lil_end);
void					print_messages(t_ssl *ssl, int isfile);

/*
**	parse.c
**	Functions to assist in argument parsing
*/
void					parse_flags(t_ssl *ssl, char *s1);
void					check_file(t_ssl *ssl, char *s1);
int						get_mode(char *s1);
void					check_args(t_ssl *ssl, int ac, char **av);

/*
**	handle.c
**	Functions that handle argument initialization
*/
char					*check_stdin(int *size);
void					handle_s(t_ssl *ssl, char *s1, int is_arg);
void					handle_stdin(t_ssl *ssl);
char					*nameify(t_queue *data, int is_file);

/*
**	t_queue.c
**	t_queue structure management functions
*/
void					q_init(t_queue **begin, char *name,\
						int size, int isfile);
void					q_clean(t_queue *begin);
void					q_print(t_queue *begin);

#endif
