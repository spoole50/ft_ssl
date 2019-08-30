/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 20:45:30 by spoole            #+#    #+#             */
/*   Updated: 2019/08/29 20:45:32 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA1_H
# define SHA1_H

# include "ft_ssl.h"

# define CH(x, y, z) ((x & y) ^ ((~x) & z))
# define PAR(x, y, z) (x ^ y ^ z)
# define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

# define A sha->reg[0]
# define B sha->reg[1]
# define C sha->reg[2]
# define D sha->reg[3]
# define E sha->reg[4]

# define M sha->m

typedef struct	s_sha1
{
	uint32_t	f;
	uint32_t	k;
	uint32_t	m[80];
	uint32_t	state[5];
	uint32_t	reg[5];
}				t_sha1;

#endif
