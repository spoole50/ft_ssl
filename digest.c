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

t_algorithm			*g_modes[MODE_NUM] = {md5, sha256};

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
	char			*test;
	int				i;

	clean = NULL;
	temp = NULL;
	test = NULL;
	i = 0;
	while (i < len)
	{
		ft_asprintf(&clean, "%02x", output[i]);
		if (temp != NULL)
			test = temp;
		temp = ft_strjoin(temp, clean);
		free(clean);
		free(test);
		i++;
	}
	return (temp);
}

void				digest(int mode, t_queue *data, int is_file)
{
	unsigned char	*message;

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
