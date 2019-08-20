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
	ft_printf("%s\n", filename);
	if ((stat(filename, &stats)) < 0 || (S_ISREG(stats.st_mode) != 1))
		q_init(&ssl->begin, s1, 0, -1);
	else
		q_init(&ssl->begin, filename, stats.st_size, true);
	ssl->numQ++;
}

int			get_mode(char *s1)
{
	char	*verify;
	int 	i;
	char	*test[MODE_NUM] = {"md5", "sha256"};

	i = 0;
	verify = ft_strdup(s1);
	while (s1[i] != '\0')
	{
		s1[i] = ft_tolower(s1[i]);
		i++;
	}
	i = 0;
	while (i < MODE_NUM)
		{
			if (ft_strcmp(verify, test[i]) == 0)
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