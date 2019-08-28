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
		q_clean(begin);
	ft_printf("%s\n%s\n", err, "Usage: ./ft_ssl [md5,sha25] -[pqrs] [file...]");
	exit(EXIT_FAILURE);
}

int			main(int ac, char **av)
{
	t_ssl	ssl;

	ssl.flags = 0;
	ssl.begin = NULL;
	ssl.num_q = 0;
	ssl.mode = get_mode(av[1]);
	if (ac > 2)
		check_args(&ssl, ac, av);
	else
		handle_stdin(&ssl);
	process_message(&ssl);
	print_messages(&ssl, 0);
	print_messages(&ssl, 3);
	q_clean(ssl.begin);
	return (0);
}
