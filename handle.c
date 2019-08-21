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
	if (is_arg == true)
		ssl->flags &= ~(1 << s_flag);
	q_init(&ssl->begin, s1, ft_strlen(s1), false);
	ssl->numQ++;
}

void		handle_stdin(t_ssl *ssl)
{
	char	*input;
	int		size;

	size = 0;
	input = check_stdin(&size);
	q_init(&ssl->begin, input, size, false);
	free(input);
}