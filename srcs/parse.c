/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 01:02:23 by spoole            #+#    #+#             */
/*   Updated: 2019/08/20 01:02:25 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			parse_flags(t_ssl *ssl, char *s1)
{
	int			i;
	int			flag;

	i = 1;
	flag = 0;
	while (s1[i] != '\0')
	{
		if ((flag = ft_charspn("pqrsh", s1[i])) == -1)
			err(ssl->begin, "Invalid Flag");
		ssl->flags |= (1 << flag);
		i++;
	}
}

void			check_file(t_ssl *ssl, char *s1)
{
	struct stat	stats;
	char		filename[100];

	realpath(s1, (char*)&filename);
	if ((stat(filename, &stats)) < 0 || !(stats.st_mode & S_IFREG))
	{
		if (stats.st_mode & S_IFDIR)
			q_init(&ssl->begin, s1, 0, 2);
		else
			q_init(&ssl->begin, s1, 0, 3);
	}
	else
		q_init(&ssl->begin, filename, stats.st_size, TRUE);
	ssl->num_q++;
}

int				get_mode(char *s1)
{
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	if (s1 != NULL)
	{
		if (s1[i] == '-')
			flag = 1;
		while (s1[i] != '\0')
		{
			if (flag == 1 && s1[i] == 'h')
				print_help(NULL);
			s1[i] = ft_toupper(s1[i]);
			i++;
		}
		i = -1;
		while (++i < MODE_NUM)
		{
			if (ft_strcmp(s1, g_algos[i]) == 0)
				return (i);
		}
	}
	err(NULL, "Not a valid algorithm mode");
	return (-1);
}

void			check_args(t_ssl *ssl, int ac, char **av)
{
	int			i;
	int			pfl;

	i = 2;
	pfl = 0;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			parse_flags(ssl, av[i]);
			if ((ssl->flags >> H_FLAG) & 1)
				print_help(ssl->begin);
			if (pfl == 0 && (ssl->flags >> P_FLAG) & 1)
			{
				pfl = 1;
				handle_stdin(ssl);
			}
			if ((ssl->flags >> S_FLAG) & 1)
				(++i < ac) ? handle_s(ssl, av[i], TRUE) :\
				err(ssl->begin, "invalid string with -s flag");
		}
		else
			check_file(ssl, av[i]);
		i++;
	}
}
