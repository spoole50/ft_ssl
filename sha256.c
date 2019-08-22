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

void        init_state(unsigned int *state)
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

void        sha256_transform(unsigned char *message)
{
    unsigned int    m[64];
    int i;
    int j;

    j = i = 0;
    while (i < 16)
    {
        m[i] = 
        j += 4;
        i++;
    }
}

char        *sha256(unsigned char *message, int tBytes)
{
    unsigned char data[64];
    unsigned int state[8];

    init_state((unsigned int*)&state);

    return (NULL);
}