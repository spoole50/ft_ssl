/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:07:59 by spoole            #+#    #+#             */
/*   Updated: 2019/08/21 17:08:01 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void				init_sha256(uint32_t *state)
{
	state[0] = 0x6a09e667;
	state[1] = 0xbb67ae85;
	state[2] = 0x3c6ef372;
	state[3] = 0xa54ff53a;
	state[4] = 0x510e527f;
	state[5] = 0x9b05688c;
	state[6] = 0x1f83d9ab;
	state[7] = 0x5be0cd19;
}

void				sha265_compress(t_sha256 *sha)
{
	int				i;

	i = 0;
	while (i < 64)
	{
		sha->t1 = (H + EP1(E) + CH(E, F, G) + g_consts256[i] + sha->m[i]);
		sha->t2 = EP0(A) + MAJ(A, B, C);
		H = G;
		G = F;
		F = E;
		E = D + sha->t1;
		D = C;
		C = B;
		B = A;
		A = sha->t1 + sha->t2;
		i++;
	}
}

void				sha256_process(unsigned char *message,\
					t_sha256 *sha, int block)
{
	int				i;

	i = 0;
	while (i < 16)
	{
		sha->m[i] = swap_bits32(*((uint32_t*)\
		(message + (block * 64) + (i * 4))));
		i++;
	}
	while (i < 64)
	{
		sha->m[i] = SIG1(sha->m[i - 2]) + sha->m[i - 7] +\
		SIG0(sha->m[i - 15]) + sha->m[i - 16];
		i++;
	}
}

void				sha256algo(unsigned char *message,\
					t_queue *data, t_sha256 *sha)
{
	int				block;
	int				i;

	block = 0;
	i = 0;
	while (block < data->t_bytes / 64)
	{
		sha256_process(message, sha, block);
		i = -1;
		while (++i < 8)
			sha->reg[i] = sha->state[i];
		sha265_compress(sha);
		i = -1;
		while (++i < 8)
			sha->state[i] += sha->reg[i];
		i = 0;
		block++;
	}
}

char				*sha256(unsigned char *message, t_queue *data)
{
	t_sha256		sha;
	int				i;
	unsigned char	output[32];

	i = -1;
	build_msg(message, data, 0);
	init_sha256((uint32_t*)&sha.state);
	sha256algo(message, data, &sha);
	while (++i < 8)
		sha.state[i] = swap_bits32(sha.state[i]);
	make_result((unsigned char*)&output, sha.state, 32);
	return (str_result((unsigned char*)&output, 32));
}
