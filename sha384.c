/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 10:21:59 by spoole            #+#    #+#             */
/*   Updated: 2019/08/29 10:22:01 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

void				init_sha384(uint64_t *state)
{
	state[0] = 0xcbbb9d5dc1059ed8;
	state[1] = 0x629a292a367cd507;
	state[2] = 0x9159015a3070dd17;
	state[3] = 0x152fecd8f70e5939;
	state[4] = 0x67332667ffc00b31;
	state[5] = 0x8eb44a8768581511;
	state[6] = 0xdb0c2e0d64f98fa7;
	state[7] = 0x47b5481dbefa4fa4;
}

char				*sha384(unsigned char *message, t_queue *data)
{
	t_sha512		sha;
	int				i;
	unsigned char	output[64];

	i = -1;
	build_msg(message, data, FALSE);
	init_sha384((uint64_t*)&sha.state);
	sha512algo(message, &sha, data);
	while (++i < 8)
		sha.state[i] = swap_bits64(sha.state[i]);
	make_result((unsigned char*)&output, (uint32_t*)sha.state, 48);
	return (str_result((unsigned char*)&output, 48));
}
