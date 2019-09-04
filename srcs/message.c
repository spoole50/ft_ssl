/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 23:21:48 by spoole            #+#    #+#             */
/*   Updated: 2019/08/27 23:21:49 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		test_message(unsigned char *message, t_queue *data)
{
	int		i;

	i = 0;
	while (data->t_bytes > i)
	{
		ft_printf("%p:%d: %08s\n", message + i,\
		i, ft_itoab_unsigned(*(message + i), 2));
		i++;
	}
	ft_printf("\n");
}

void		file_message(unsigned char *message, t_queue *data)
{
	int		fd;
	int		reads;

	reads = 10;
	fd = open(data->name, O_RDONLY);
	if ((uint64_t)(reads = read(fd, message,\
	(size_t)data->byte_size)) == data->byte_size)
		if (reads == 0)
			err(data, "File Read Error");
}

void		build_msg(unsigned char *formatted_msg,\
t_queue *data, int is_lil_end)
{
	formatted_msg[data->byte_size] = 128;
	*(uint64_t *)(formatted_msg + data->t_bytes - 8) =\
		is_lil_end ? 8 * data->byte_size : swap_bits64(8 * data->byte_size);
}

void		flag_help(t_ssl *ssl, t_queue *temp)
{
	if ((ssl->flags >> P_FLAG) & 1)
	{
		ssl->flags &= ~(1 << P_FLAG);
		ft_printf("%s%s\n", temp->name, temp->result);
	}
	else if ((ssl->flags >> R_FLAG) & 1)
		ft_printf("%s %s\n", temp->result, nameify(temp, temp->is_file));
	else
		ft_printf("%s (%s) = %s\n", g_algos[ssl->mode],\
		nameify(temp, temp->is_file), temp->result);
}

void		print_messages(t_ssl *ssl, int isfile)
{
	t_queue	*temp;

	temp = ssl->begin;
	while (temp != NULL)
	{
		if (temp->is_file >= isfile)
		{
			if (temp->is_file >= 2)
				ft_printf("ft_ssl %s: %s: %s\n",\
				g_algos[ssl->mode], temp->name,\
				(temp->is_file == 2) ? "Is a directory"\
				: "No such file or directory");
			else if (!((ssl->flags >> Q_FLAG) & 1))
				flag_help(ssl, temp);
			else
				ft_printf("%s\n", temp->result);
		}
		temp = temp->next;
	}
}
