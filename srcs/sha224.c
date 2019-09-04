/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 12:24:26 by spoole            #+#    #+#             */
/*   Updated: 2019/08/29 12:24:28 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

void				init_sha224(uint32_t *state)
{
	state[0] = 0xc1059ed8;
	state[1] = 0x367cd507;
	state[2] = 0x3070dd17;
	state[3] = 0xf70e5939;
	state[4] = 0xffc00b31;
	state[5] = 0x68581511;
	state[6] = 0x64f98fa7;
	state[7] = 0xbefa4fa4;
}

char				*sha224(unsigned char *message, t_queue *data)
{
	t_sha256		sha;
	int				i;
	unsigned char	output[32];

	i = -1;
	build_msg(message, data, 0);
	init_sha224((uint32_t*)&sha.state);
	sha256algo(message, data, &sha);
	while (++i < 8)
		sha.state[i] = swap_bits32(sha.state[i]);
	make_result((unsigned char*)&output, sha.state, 28);
	return (str_result((unsigned char*)&output, 28));
}
