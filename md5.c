/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:59:02 by spoole            #+#    #+#             */
/*   Updated: 2019/08/13 21:59:04 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void    make_result(unsigned char *output, uint32_t *input, int len)
{
	int i;
	int j;

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

char        *str_result(unsigned char *output, int len)
{
	char    *temp;
	char    *clean;
	char    *test;
	int     i = 0;
	clean = temp = test = NULL;
	while (i < len)
	{
		ft_asprintf(&clean,"%02x", output[i]);
		if (temp != NULL)
			test = temp;
		temp = ft_strjoin(temp, clean);
		free(clean);
		free(test);
		i++;
	}
	return (temp);
}

void		md5_compress(int i, t_md5 *md5)
{
	if (i <= 15)
	{
		md5->T = F(md5->b,md5->c,md5->d);
		md5->g = i; 
	}
	else if (i <= 31)
	{
		md5->T = G(md5->b,md5->c,md5->d);
		md5->g = ((5 * i) + 1) % 16;
	}
	else if (i <= 47)
	{
		md5->T = H(md5->b,md5->c,md5->d);
		md5->g = ((3 * i) + 5) % 16;
	}
	else if (i <= 63)
	{
		md5->T = I(md5->b,md5->c,md5->d);
		md5->g = (7 * i) % 16;
	}
}

void		md5_algo(t_md5 *md5, t_queue *data, unsigned char *message)
{
	int 	block;
	int 	i;

	block = 0;
	i = 0;
	while (block < data->tBytes/64)
	{
		md5->a = md5->state[A];
		md5->b = md5->state[B];
		md5->c = md5->state[C];
		md5->d = md5->state[D];
		while (i < 64)
		{
			md5_compress(i, md5);
			md5->T = md5->T + md5->a + consts[i] + (*(uint32_t*)(message + ((block * 64) + (4 * md5->g))));
			md5->a = md5->d;
			md5->d = md5->c;
			md5->c = md5->b;
			md5->b = md5->b + ROTL(md5->T, shift[i]);
			i++;
		}
		md5->state[A] = md5->state[A] + md5->a;
		md5->state[B] = md5->state[B] + md5->b;
		md5->state[C] = md5->state[C] + md5->c;
		md5->state[D] = md5->state[D] + md5->d;
		i = 0;
		block++;
	}
}

char    *md5(unsigned char *message, t_queue *data)
{
	t_md5 md5;
	unsigned char output[16];

	md5.state[A] = a0;
	md5.state[B] = b0;
	md5.state[C] = c0;
	md5.state[D] = d0;
	*(message + (data->byte_size)) = 128;
	(*(uint64_t*)(message + ((data->tBytes) - 8))) = (uint64_t)(data->byte_size * 8);
	md5_algo(&md5, data, message);
	make_result((unsigned char*)&output, md5.state, 16);
	return (str_result((unsigned char*)&output, 16));
}