/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 14:31:11 by spoole            #+#    #+#             */
/*   Updated: 2019/08/28 14:31:15 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

void				init_sha512(uint64_t *state)
{
	state[0] = 0x6a09e667f3bcc908;
	state[1] = 0xbb67ae8584caa73b;
	state[2] = 0x3c6ef372fe94f82b;
	state[3] = 0xa54ff53a5f1d36f1;
	state[4] = 0x510e527fade682d1;
	state[5] = 0x9b05688c2b3e6c1f;
	state[6] = 0x1f83d9abfb41bd6b;
	state[7] = 0x5be0cd19137e2179;
}

void				sha512_compress(t_sha512 *sha)
{
	int				i;

	i = 0;
	while (i < 80)
	{
		sha->t1 = (H + SUM1(E) + CH(E, F, G) + g_consts512[i] + sha->m[i]);
		sha->t2 = SUM0(A) + MAJ(A, B, C);
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

void				sha512_process(unsigned char *message,\
					t_sha512 *sha, int block)
{
	int				i;

	i = 0;
	while (i < 16)
	{
		sha->m[i] = swap_bits64(*((uint64_t*)\
		(message + (block * 128) + (i * 8))));
		i++;
	}
	while (i < 80)
	{
		sha->m[i] = SIGMA1(sha->m[i - 2]) + sha->m[i - 7] +\
		SIGMA0(sha->m[i - 15]) + sha->m[i - 16];
		i++;
	}
}

void				sha512algo(unsigned char *message,\
					t_sha512 *sha, t_queue *data)
{
	int				block;
	int				i;

	block = 0;
	i = 0;
	while (block < data->t_bytes / 128)
	{
		sha512_process(message, sha, block);
		i = -1;
		while (++i < 8)
			sha->reg[i] = sha->state[i];
		sha512_compress(sha);
		i = -1;
		while (++i < 8)
			sha->state[i] += sha->reg[i];
		i = 0;
		block++;
	}
}

char				*sha512(unsigned char *message, t_queue *data)
{
	t_sha512		sha;
	int				i;
	unsigned char	output[64];

	i = -1;
	build_msg(message, data, FALSE);
	init_sha512((uint64_t*)&sha.state);
	sha512algo(message, &sha, data);
	while (++i < 8)
		sha.state[i] = swap_bits64(sha.state[i]);
	make_result((unsigned char*)&output, (uint32_t*)sha.state, 64);
	return (str_result((unsigned char*)&output, 64));
}
