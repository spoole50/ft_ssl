/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 17:08:07 by spoole            #+#    #+#             */
/*   Updated: 2019/08/21 17:08:08 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "ft_ssl.h"

# define CH(x,y,z) (((x) & ((y) ^ (z))) ^ (z))
# define MAJ(x,y,z) (((x) & ((y) | (z))) | ((y) & (z)))

# define EP0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
# define EP1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
# define SIG0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3))
# define SIG1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10))

# define A sha->reg[0]
# define B sha->reg[1]
# define C sha->reg[2]
# define D sha->reg[3]
# define E sha->reg[4]
# define F sha->reg[5]
# define G sha->reg[6]
# define H sha->reg[7]

static const unsigned int	g_consts256[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

typedef struct		s_sha256
{
	uint32_t		m[64];
	uint32_t		state[8];
	uint32_t		reg[8];
	uint32_t		j;
	uint32_t		t1;
	uint32_t		t2;
}					t_sha256;

void				sha256algo(unsigned char *message,\
					t_queue *data, t_sha256 *sha);

#endif
