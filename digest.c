/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 21:29:10 by spoole            #+#    #+#             */
/*   Updated: 2019/08/27 21:29:12 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_algorithm			*g_modes[MODE_NUM] = {md5, sha256, sha512};

void				make_result(unsigned char *output, uint32_t *input, int len)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
		j += 4;
		i++;
	}
}

char				*str_result(unsigned char *output, int len)
{
	char			*temp;
	char			*clean;
	int				i;

	clean = NULL;
	temp = NULL;
	i = 0;
	while (i < len)
	{
		clean = temp;
		if (i == 0)
			ft_asprintf(&temp, "%02x", output[i]);
		else
			ft_asprintf(&temp, "%s%02x", temp, output[i]);
		free(clean);
		i++;
	}
	return (temp);
}

void				calc_tsize(int mode, t_queue *data)
{
	uint64_t size;

	size = data->byte_size;
	if (mode <= 1)
	{
		size += 9;
		while (size % 64 != 0)
			size++;
	}
	else if (mode == 2)
	{
		size += 17;
		while (size % 128 != 0)
			size++;
	}
	if (size != data->byte_size)
		data->t_bytes = size;
}

void				digest(int mode, t_queue *data, int is_file)
{
	unsigned char	*message;

	calc_tsize(mode, data);
	message = (unsigned char *)malloc(sizeof(unsigned char) * data->t_bytes);
	ft_bzero(message, data->t_bytes);
	if (!is_file)
		ft_memcpy(message, data->name, data->byte_size);
	else
		file_message((unsigned char*)message, data);
	data->result = g_modes[mode](message, data);
	free(message);
}

void				process_message(t_ssl *ssl)
{
	t_queue			*temp;

	temp = ssl->begin;
	while (temp != NULL)
	{
		if (temp->is_file == FALSE)
			digest(ssl->mode, temp, 0);
		temp = temp->next;
	}
	temp = ssl->begin;
	while (temp != NULL)
	{
		if (temp->byte_size != 0 && temp->is_file == TRUE)
			digest(ssl->mode, temp, 1);
		temp = temp->next;
	}
}
