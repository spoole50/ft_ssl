/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 19:01:58 by spoole            #+#    #+#             */
/*   Updated: 2019/08/29 19:02:00 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha1.h"

void			sha1_process(unsigned char *message, t_sha1 *sha, int block)
{
	int			i;

	i = 0;
	while (i < 16)
	{
		M[i] = swap_bits32(*((uint32_t*)(message + (block * 64) + (i * 4))));
		i++;
	}
	while (i < 80)
	{
		M[i] = ROTL(((M[i - 3]) ^ (M[i - 8]) ^ (M[i - 14]) ^ (M[i - 16])), 1);
		i++;
	}
}

void			sha1_set(t_sha1 *sha, int i)
{
	if (i < 20)
	{
		sha->f = CH(B, C, D);
		sha->k = 0x5a827999;
	}
	else if (i >= 20 && i < 40)
	{
		sha->f = PAR(B, C, D);
		sha->k = 0x6ed9eba1;
	}
	else if (i >= 40 && i < 60)
	{
		sha->f = MAJ(B, C, D);
		sha->k = 0x8f1bbcdc;
	}
	else
	{
		sha->f = PAR(B, C, D);
		sha->k = 0xca62c1d6;
	}
}

void			sha1_compress(t_sha1 *sha)
{
	int			i;
	uint32_t	temp;

	i = 0;
	while (i < 80)
	{
		sha1_set(sha, i);
		temp = (ROTL(A, 5)) + sha->f + E + sha->k + M[i];
		E = D;
		D = C;
		C = ROTL(B, 30);
		B = A;
		A = temp;
		i++;
	}
}

void			sha1algo(unsigned char *message, t_queue *data, t_sha1 *sha)
{
	int			block;
	int			i;

	block = 0;
	sha->state[0] = 0x67452301;
	sha->state[1] = 0xEFCDAB89;
	sha->state[2] = 0x98BADCFE;
	sha->state[3] = 0x10325476;
	sha->state[4] = 0xC3D2E1F0;
	while (block < data->t_bytes / 64)
	{
		i = -1;
		sha1_process(message, sha, block);
		while (++i < 8)
			sha->reg[i] = sha->state[i];
		sha1_compress(sha);
		i = -1;
		while (++i < 8)
			sha->state[i] += sha->reg[i];
		block++;
	}
}

char			*sha1(unsigned char *message, t_queue *data)
{
	t_sha1		sha;
	int			i;
	char		*res;

	i = 0;
	res = NULL;
	build_msg(message, data, 0);
	sha1algo(message, data, &sha);
	ft_asprintf(&res, "%08x%08x%08x%08x%08x",\
	sha.state[0], sha.state[1],\
	sha.state[2], sha.state[3], sha.state[4]);
	return (res);
}
