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

algorithm	*modes[MODE_NUM] = {md5};

void		err(t_queue *begin, char *err)
{
	if (begin != NULL)
		cleanQ(begin);
	char	*usage = "Usage: ./ft_ssl [md5,sha25] -[pqrs] [file...]";
	ft_printf("%s\n%s\n", err, usage);
	exit(EXIT_FAILURE);
}

void			str_message(unsigned char *message, t_queue *data)
{
	ft_memcpy(message, data->name, data->bit_size/8);
	*(message + (data->bit_size/8)) = 128;
	(*(uint64_t*)(message + ((data->block_num * 64) - 8))) = (uint64_t)data->bit_size;
}

void			test_message(unsigned char *message, t_queue *data)
{
	int i;

	i = 0;
	while (data->block_num * 64 > i)
	{
		ft_printf("%p:%d: %08s\n", message + i,i,ft_itoab_unsigned(*(message + i),2));
		i++;
	}
	ft_printf("\n");
}

void			digest(int mode, t_queue *data)
{
	unsigned char	message[data->block_num * 64];

	ft_bzero(&message, data->block_num * 64);
	str_message((unsigned char*)&message, data);
	//test_message((unsigned char*)&message, data);
	data->result = modes[mode](message, data->block_num);	
}

void			process_message(t_ssl *ssl)
{
	t_queue		*temp;

	temp = ssl->begin;
	while (temp != NULL)
	{
		if (temp->is_file == false)
			digest(ssl->mode, temp);
		temp = temp->next;	
	}
}

void		print_messages(t_ssl *ssl)
{
	t_queue	*temp;

	temp = ssl->begin;
	while (temp != NULL)
	{
		ft_printf("%s", temp->result);
		temp = temp->next;
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
	print_messages(&ssl);
	cleanQ(ssl.begin);	
	return (0);
}