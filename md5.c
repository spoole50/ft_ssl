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

void				md5_compress(int i, t_md5 *md5)
{
	if (i <= 15)
	{
		md5->t = F(md5->b, md5->c, md5->d);
		md5->g = i;
	}
	else if (i <= 31)
	{
		md5->t = G(md5->b, md5->c, md5->d);
		md5->g = ((5 * i) + 1) % 16;
	}
	else if (i <= 47)
	{
		md5->t = H(md5->b, md5->c, md5->d);
		md5->g = ((3 * i) + 5) % 16;
	}
	else if (i <= 63)
	{
		md5->t = I(md5->b, md5->c, md5->d);
		md5->g = (7 * i) % 16;
	}
}

void				md5_algo(t_md5 *md5, t_queue *data, unsigned char *message)
{
	while (md5->block < data->t_bytes / 64)
	{
		md5->a = md5->state[A];
		md5->b = md5->state[B];
		md5->c = md5->state[C];
		md5->d = md5->state[D];
		while (md5->i < 64)
		{
			md5_compress(md5->i, md5);
			md5->t = md5->t + md5->a + g_consts[md5->i] +\
			(*(uint32_t*)(message + ((md5->block * 64) + (4 * md5->g))));
			md5->a = md5->d;
			md5->d = md5->c;
			md5->c = md5->b;
			md5->b = md5->b + ROTL(md5->t, g_shift[md5->i]);
			md5->i++;
		}
		md5->state[A] = md5->state[A] + md5->a;
		md5->state[B] = md5->state[B] + md5->b;
		md5->state[C] = md5->state[C] + md5->c;
		md5->state[D] = md5->state[D] + md5->d;
		md5->i = 0;
		md5->block++;
	}
}

char				*md5(unsigned char *message, t_queue *data)
{
	t_md5			md5;
	unsigned char	output[16];

	md5.state[A] = A0;
	md5.state[B] = B0;
	md5.state[C] = C0;
	md5.state[D] = D0;
	md5.i = 0;
	md5.block = 0;
	build_msg(message, data, 1);
	md5_algo(&md5, data, message);
	make_result((unsigned char*)&output, md5.state, 16);
	return (str_result((unsigned char*)&output, 16));
}
