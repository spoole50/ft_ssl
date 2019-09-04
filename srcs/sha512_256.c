/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:54:00 by spoole            #+#    #+#             */
/*   Updated: 2019/08/29 13:54:02 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha512.h"

void				init_sha512_256(uint64_t *state)
{
	state[0] = 0x22312194FC2BF72C;
	state[1] = 0x9F555FA3C84C64C2;
	state[2] = 0x2393B86B6F53B151;
	state[3] = 0x963877195940EABD;
	state[4] = 0x96283EE2A88EFFE3;
	state[5] = 0xBE5E1E2553863992;
	state[6] = 0x2B0199FC2C85B8AA;
	state[7] = 0x0EB72DDC81C52CA2;
}

char				*sha512_256(unsigned char *message, t_queue *data)
{
	t_sha512		sha;
	int				i;
	unsigned char	output[64];

	i = -1;
	build_msg(message, data, FALSE);
	init_sha512_256((uint64_t*)&sha.state);
	sha512algo(message, &sha, data);
	while (++i < 8)
		sha.state[i] = swap_bits64(sha.state[i]);
	make_result((unsigned char*)&output, (uint32_t*)sha.state, 32);
	return (str_result((unsigned char*)&output, 32));
}
