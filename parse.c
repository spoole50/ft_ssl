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
	if ((stat(filename, &stats)) < 0 || (S_ISREG(stats.st_mode) != 1))
		q_init(&ssl->begin, s1, 0, -1);
	else
		q_init(&ssl->begin, filename, stats.st_size, true);
	ssl->numQ++;
}

int			get_mode(char *s1)
{
	int 	i;
	

	i = 0;
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{
			s1[i] = ft_toupper(s1[i]);
			i++;
		}
		i = -1;
		while (++i < MODE_NUM)
			{
				if (ft_strcmp(s1, test[i]) == 0)
					return (i);
			}
	}
	err(NULL, "Not a valid algorithm mode");
	return (-1);
}

void		check_args(t_ssl *ssl, int ac, char **av)
{
	int i;
	int	pfl;

	i = 2;
	pfl = 0;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			parse_flags(ssl, av[i]);
			if (pfl == 0 && (ssl->flags >> p_flag) & 1)
			{
				pfl = 1;
				handle_stdin(ssl);
			}
			else if ((ssl->flags >> s_flag) & 1)
				(++i < ac) ? handle_s(ssl, av[i], true):\
				err(ssl->begin, "invalid string with -s flag");
		}
		else
			check_file(ssl, av[i]);
		i++;
	}
}