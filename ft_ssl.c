/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 13:18:39 by spoole            #+#    #+#             */
/*   Updated: 2019/08/12 13:18:53 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*modes[num_modes] = {"md5", "sha256"};

void		err(t_queue *begin, char *err)
{
	if (begin != NULL)
		cleanQ(begin);
	char	*usage = "Usage: ./ft_ssl [md5,sha25] -[pqrs] [file...]";
	ft_printf("%s\n%s\n", err, usage);
	exit(EXIT_FAILURE);
}

char		*check_stdin(int *size)
{
	char	*res;
	char	*tmp;
	char	*clean;
	int		writes;

	res = NULL;
	tmp = NULL;
	tmp = ft_strbuf(tmp, 64);
	writes = 0;
	while ((writes = read(STDIN_FILENO, tmp, 64)) != 0)
	{
		if (tmp != NULL)
		{
			clean = res;
			res = ft_strjoin(res, tmp);
			free(clean);
		}
		*size += writes;
	}
	free(tmp);
	if (*size > 0)
		return (res);
	else
		return (NULL);
}

void		parse_flags(t_ssl *ssl, char *s1)
{
	int i;
	int	flag;

	i = 1;
	flag = 0;
	while (s1[i] != '\0')
	{
		if ((flag = ft_charspn("pqrs", s1[i])) == -1)
			err(ssl->begin, "Invalid Flag");
		ssl->flags |= (1 << flag);
		i++;
	}
}

void		check_file(t_ssl *ssl, char *s1)
{
	struct stat stats;
	char		filename[100];

	realpath(s1, (char*)&filename);
	ft_printf("%s\n", filename);
	if ((stat(filename, &stats)) < 0 || (S_ISREG(stats.st_mode) != 1))
		q_init(&ssl->begin, s1, 0, -1);
	else
		q_init(&ssl->begin, filename, stats.st_size, true);
	ssl->numQ++;
}

void		handle_s(t_ssl *ssl, char *s1, int is_arg)
{
	if (is_arg == true)
		ssl->flags &= ~(1 << s_flag);
	q_init(&ssl->begin, s1, sizeof(s1), false);
	ssl->numQ++;
}

void		handle_stdin(t_ssl *ssl)
{
	char	*input;
	int		size;

	input = check_stdin(&size);
	q_init(&ssl->begin, input, size, false);
	free(input);
}

int			get_mode(char *s1)
{
	char	*verify;
	int 	i;

	i = 0;
	verify = ft_strdup(s1);
	while (s1[i] != '\0')
	{
		s1[i] = ft_tolower(s1[i]);
		i++;
	}
	i = 0;
	while (i < num_modes)
		{
			if (ft_strcmp(verify, modes[i]) == 0)
				return (i);
		}
	free(verify);
	err(NULL, "Not a valid algorithm mode");
	return (-1);
}

void		check_args(t_ssl *ssl, int ac, char **av)
{
	int i;

	i = 1;
	ssl->mode = get_mode(av[i++]);
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			parse_flags(ssl, av[i]);
			if ((ssl->flags >> s_flag) & 1)
				(++i < ac) ? handle_s(ssl, av[i], true):\
				err(ssl->begin, "invalid string with -s flag");
		}
		else
			check_file(ssl, av[i]);
		i++;
	}
	if ((ssl->flags >> p_flag) & 1)
		handle_stdin(ssl);
}

void			str_message(u_int32_t **message, t_queue *data)
{
	int x;
	int	y;
	int	bits;
	char	*temp;

	x = 0;
	y = 0;
	bits = data->bit_size;
	temp = data->name;
	while (x < data->block_num && bits > 65)
	{
		while (y < 16)
		{
			ft_memcpy((void*)&message[x][y], temp, 512/16);
			y++;
			bits -= 32;
		}
		y = 0;
		x++;
	}
}

void			digest(int mode, t_queue *data)
{
	u_int32_t	message[data->block_num][16];

	str_message((uint32_t**)&message, data);
	mode++;
}

	

void			process_message(t_ssl *ssl)
{
	t_queue		*temp;

	temp = ssl->begin;
	while (temp != NULL)
	{
		if (temp->is_file == false)
			if (sizeof(temp->name)*8 == temp->bit_size)
				digest(ssl->mode, temp);	
	}
}

int			main(int ac, char **av)
{
	t_ssl	ssl;

	ssl.flags = 0;
	ssl.begin = NULL;
	ssl.numQ = 0;
	if (ac > 1)
		check_args(&ssl, ac, av);
	else
		handle_stdin(&ssl);
		printQ(ssl.begin);
	process_message(&ssl);
	cleanQ(ssl.begin);	
	return (0);
}