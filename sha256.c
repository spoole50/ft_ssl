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

void    make_result(unsigned char *output, uint32_t *input, int len);
char        *str_result(unsigned char *output, int len);

void        init_sha256(uint32_t *state)
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

void		prep_message(unsigned char *message, t_queue *data)
{
	uint64_t i;

	i = 0;
	while (i < data->byte_size/4)
	{
		*((uint32_t*)(message + i)) = SWAP_BITS32(*((uint32_t*)(message + i)));
		i += 4;
	}
	*(message + (data->byte_size)) = 128;
	(*(uint64_t*)(message + ((data->tBytes) - 8))) = SWAP_BITS64((uint64_t)(data->byte_size * 8));
}

char        *sha256(unsigned char *message, t_queue *data)
{
    t_sha256	sha;
	int block;
	int	i;
	unsigned char output[32];
	
	block = 0;
	i = 0;
	prep_message(message, data);
	init_sha256((uint32_t*)&sha.state);
	while (block < data->tBytes/64)
	{
		while (i < 16)
		{
			sha.m[i] = *((uint32_t*)(message + (block * 64) + i));
			i++;
		}
		while (i < 64)
		{
			sha.m[i] = SIG1(sha.m[i - 2]) + sha.m[i - 7] + SIG0(sha.m[i - 15]) + sha.m[i - 16];
			i++;
		}
		i = -1;
		while (++i < 8)
			sha.reg[i] = sha.state[i];
		i = 0;
		while (i < 64)
		{
			sha.t1 = (h + EP1(e) + CH(e,f,g) + consts[i] + sha.m[i]);
			sha.t2 = EP0(a) + MAJ(a,b,c);
			h = g;
			g = f;
			f = e;
			e = d + sha.t1;
			d = c;
			c = b;
			b = a;
			a = sha.t1 + sha.t2;
			i++;
		}
		i = -1;
		while (++i < 8)
			sha.state[i] += sha.reg[i];
		i = 0;
		block++;
	}
	i = -1;
	while (++i < 8)
		sha.state[i] = SWAP_BITS32(sha.state[i]);
	make_result((unsigned char*)&output, sha.state, 32);
    return (str_result((unsigned char*)&output, 32));
}