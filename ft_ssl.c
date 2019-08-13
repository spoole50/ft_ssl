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

void		err(t_queue *begin, char *err)
{
	if (begin != NULL)
		cleanQ(begin);
	char	*usage = "Usage: ./ft_ssl -[pqrs] [file...]";
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
	tmp = ft_strbuf(tmp, 512);
	writes = 0;
	while ((writes = read(STDIN_FILENO, tmp, 512)) != 0)
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
			err(ssl->begin, "Inavlid File");
	q_init(&ssl->begin, s1, stats.st_size, true);
}

void		handle_s(t_ssl *ssl, char *s1, int is_arg)
{
	if (is_arg == true)
		ssl->flags &= ~(1 << s_flag);
	q_init(&ssl->begin, s1, sizeof(s1), false);
}

void		check_args(t_ssl *ssl, int ac, char **av)
{
	int i;

	i = 1;
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
	/*if ((ssl->flags >> p_flag) & 1)
		handle_p();
		*/
}

int			main(int ac, char **av)
{
	t_ssl	ssl;

	ssl.flags = 0;
	ssl.begin = NULL;
	if (ac > 1)
		check_args(&ssl, ac, av);
	/*else
		read in stdin
		*/
	cleanQ(ssl.begin);	
	return (0);
}