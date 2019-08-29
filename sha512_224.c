/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_224.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:17:47 by spoole            #+#    #+#             */
/*   Updated: 2019/08/29 13:17:50 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

void				init_sha512_224(uint64_t *state)
{
	state[0] = 0x8C3D37C819544DA2;
	state[1] = 0x73E1996689DCD4D6;
	state[2] = 0x1DFAB7AE32FF9C82;
	state[3] = 0x679DD514582F9FCF;
	state[4] = 0x0F6D2B697BD44DA8;
	state[5] = 0x77E36F7304C48942;
	state[6] = 0x3F9D85A86A1D36C8;
	state[7] = 0x1112E6AD91D692A1;
}

char				*sha512_224(unsigned char *message, t_queue *data)
{
	t_sha512		sha;
	int				i;
	unsigned char	output[64];

	i = -1;
	build_msg(message, data, FALSE);
	init_sha512_224((uint64_t*)&sha.state);
	sha512algo(message, &sha, data);
	while (++i < 8)
		sha.state[i] = swap_bits64(sha.state[i]);
	make_result((unsigned char*)&output, (uint32_t*)sha.state, 28);
	return (str_result((unsigned char*)&output, 28));
}
