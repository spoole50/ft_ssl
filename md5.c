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

uint32_t    left(uint32_t T, int shift)
{
    return ( (T << shift) | (T >> (32 - shift)) );
}

char    *md5(unsigned char *message, int block_num)
{
    int block;
    int words;
    int i;
    uint32_t state[4];
    uint32_t T, g;
    uint32_t a, b, c, d;
    char    *result;

    state[A] = a0;
    state[B] = b0;
    state[C] = c0;
    state[D] = d0;

    block = 0;
    words = 0;
    i = 0;
    while (block < block_num)
    {
        T = g = a = b = c = d = 0;
        a = a0;
        b = b0;
        c = c0;
        d = d0;
        while (i < 64)
        {
            if (i <= 15)
            {
                T = F(b,c,d);
                g = i; 
            }
            else if (i <= 31)
            {
                T = G(b,c,d);
                g = ((5 * i) + 1) % 16;
            }
            else if (i <= 47)
            {
                T = H(b,c,d);
                g = ((3 * i) + 5) % 16;
            }
            else if (i <= 63)
            {
                T = I(b,c,d);
                g = (7 * i) % 16;
            }
            T = T + a + consts[i] + *(uint32_t*)(message + ((block * 64) + (4 * g)));
            a = d;
            d = c;
            c = b;
            b = b + left(T, shift[i]);
            i++;
        }
        state[A] = state[A] + a;
        state[B] = state[B] + b;
        state[C] = state[C] + c;
        state[D] = state[D] + d;
        i = 0;
        block++;
    }
    ft_asprintf(&result, "md5: %x %x %x %x\n", state[A], state[B], state[C], state[D]);
    return (result);
}