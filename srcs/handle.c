/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 01:07:07 by spoole            #+#    #+#             */
/*   Updated: 2019/08/20 01:07:09 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
			bzero(tmp, 64);
		}
		*size += writes;
	}
	free(tmp);
	if (*size > 0)
		return (res);
	else
		return (NULL);
}

void		handle_s(t_ssl *ssl, char *s1, int is_arg)
{
	if (is_arg == TRUE)
		ssl->flags &= ~(1 << S_FLAG);
	q_init(&ssl->begin, s1, ft_strlen(s1), FALSE);
	ssl->num_q++;
}

void		handle_stdin(t_ssl *ssl)
{
	char	*input;
	int		size;

	size = 0;
	input = check_stdin(&size);
	q_init(&ssl->begin, input, size, FALSE);
	free(input);
}

void		clean_newline(char *s1)
{
	int		i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '\n')
			s1[i] = (s1[i + 1] == '\0') ? '\0' : ' ';
		i++;
	}
}

char		*nameify(t_queue *data, int is_file)
{
	int		i;
	char	*clean;

	clean = NULL;
	i = ft_strlen(data->name);
	if (is_file == TRUE)
	{
		while (data->name[i - 1] != '/')
			i--;
		return (data->name + i);
	}
	else
	{
		clean_newline(data->name);
		clean = data->name;
		ft_asprintf(&data->name, "\"%s\"", clean);
		free(clean);
	}
	return (data->name);
}
