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

algorithm	*modes[MODE_NUM] = {md5, sha256};

void		err(t_queue *begin, char *err)
{
	if (begin != NULL)
		cleanQ(begin);
	char	*usage = "Usage: ./ft_ssl [md5,sha25] -[pqrs] [file...]";
	ft_printf("%s\n%s\n", err, usage);
	exit(EXIT_FAILURE);
}

uint64_t swap_uint64( uint64_t val )
{
    val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
    val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
    return (val << 32) | (val >> 32);
}

void			str_message(unsigned char *message, t_queue *data)
{
	ft_memcpy(message, data->name, data->byte_size);
	*(message + (data->byte_size)) = 128;
	(*(uint64_t*)(message + ((data->tBytes) - 8))) = (uint64_t)(data->byte_size * 8);
}

void			test_message(unsigned char *message, t_queue *data)
{
	int i;

	i = 0;
	while (data->tBytes > i)
	{
		ft_printf("%p:%d: %08s\n", message + i,i,ft_itoab_unsigned(*(message + i),2));
		i++;
	}
	ft_printf("\n");
}

void			file_message(unsigned char *message, t_queue *data)
{
	int	fd;
	int	reads;
	
	reads = 10;
	fd = open(data->name, O_RDONLY);
	if ((uint64_t)(reads = read(fd, message, (size_t)data->byte_size)) == data->byte_size)
		if (reads == 0)
			err(data, "File Read Error");
	*(message + (data->byte_size)) = 128;
	(*(uint64_t*)(message + ((data->tBytes) - 8))) = (uint64_t)(data->byte_size*8);
}

void			digest(int mode, t_queue *data, int is_file)
{
	unsigned char *message;
	
	message = (unsigned char *)malloc(sizeof(unsigned char) * data->tBytes);
	ft_bzero(message, data->tBytes);
	if (!is_file)
		str_message((unsigned char*)message, data);
	else
		file_message((unsigned char*)message, data);
	//test_message((unsigned char*)&message, data);
	data->result = modes[mode](message, data->tBytes);
	free(message);
}

void			process_message(t_ssl *ssl)
{
	t_queue		*temp;

	temp = ssl->begin;
	while (temp != NULL)
	{
		if (temp->is_file == false)
			digest(ssl->mode, temp, 0);
		temp = temp->next;	
	}
	temp = ssl->begin;
	while (temp != NULL)
	{
		if (temp->byte_size != 0 && temp->is_file == true)
			digest(ssl->mode, temp, 1);
		temp = temp->next;
	}
}

char		*nameify(t_queue *data, int is_file)
{
	int i;
	char	*clean;

	clean = NULL;
	i = ft_strlen(data->name);
	if (is_file == 1)
	{
		while (data->name[i - 1] != '/')
			i--;
		return (data->name + i);
	}
	else
	{
		clean = data->name;
		ft_asprintf(&data->name, "\"%s\"", clean);
		free(clean);
	}
	return (data->name);
}

void		print_messages(t_ssl *ssl, int _is_file)
{
	t_queue	*temp;

	temp = ssl->begin;
	while (temp != NULL)
	{
		if (temp->is_file == _is_file)
		{
			if (temp->byte_size == 0)
				ft_printf("ft_ssl %s: %s: No such file or directory\n", test[ssl->mode], temp->name);
			else if (!((ssl->flags >> q_flag) & 1))
			{
				if ((ssl->flags >> p_flag) & 1)
				{
					ssl->flags &= ~(1 << p_flag);
					ft_printf("%s%s\n", temp->name, temp->result);
				}
				else if ((ssl->flags >> r_flag) & 1)
					ft_printf("%s %s\n", temp->result, nameify(temp, _is_file));
				else
					ft_printf("%s (%s) = %s\n", test[ssl->mode], nameify(temp, _is_file), temp->result);
			}
			else
				ft_printf("%s\n", temp->result);
		}	
		temp = temp->next;
	}
}

int			main(int ac, char **av)
{
	t_ssl	ssl;

	ssl.flags = 0;
	ssl.begin = NULL;
	ssl.numQ = 0;
	ssl.mode = get_mode(av[1]);
	if (ac > 2)
		check_args(&ssl, ac, av);
	else
		handle_stdin(&ssl);
	//printQ(ssl.begin);
	process_message(&ssl);
	print_messages(&ssl, 0);
	print_messages(&ssl, 1);
	cleanQ(ssl.begin);	
	return (0);
}