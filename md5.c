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

void    make_result(unsigned char *output, uint32_t *input, int len)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (j < len)
    {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
        j += 4;
        i++;
    }
}

char        *str_result(unsigned char *output)
{
    char    *temp;
    char    *clean;
    char    *test;
    int     i = 0;
    clean = temp = test = NULL;
    while (i < 16)
    {
        ft_asprintf(&clean,"%02x", output[i]);
        if (temp != NULL)
            test = temp;
        temp = ft_strjoin(temp, clean);
        free(clean);
        free(test);
        i++;
    }
    return (temp);
}

char    *md5(unsigned char *message, int tBytes)
{
    int block;
    int i;
    uint32_t state[4];
    uint32_t T, g;
    uint32_t a, b, c, d;

    state[A] = a0;
    state[B] = b0;
    state[C] = c0;
    state[D] = d0;

    block = 0;
    i = 0;
    while (block < tBytes/64)
    {
        T = g = a = b = c = d = 0;
        a = state[A];
        b = state[B];
        c = state[C];
        d = state[D];
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
            T = T + a + consts[i] + (*(uint32_t*)(message + ((block * 64) + (4 * g))));
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
    unsigned char output[16];
    make_result((unsigned char*)&output, state, 16);
    return (str_result((unsigned char*)&output));
}