/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 11:58:20 by spoole            #+#    #+#             */
/*   Updated: 2019/08/13 11:58:21 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
#define MD5_H

# include "ft_ssl.h"

typedef struct		s_md5
{
	UINT4 			state[4];
	UINT4			count[2];
	unsigned char	buffer[64];
}					t_md5;

/*
** Basic MD5 Functions
 */
# define F(x, y, z) ((x & y) | ((~x) & z))
# define G(x, y, z) ((x & z) | (y & (~z)))
# define H(x, y, z) (x ^ y ^ z)
# define I(x, y, z) (y ^ (x | (~z)))

void		init_buff(t_md5 *md5)
{
	md5->state[0] = 0x67452301;
	md5->state[1] = 0xefcdab89;
	md5->state[2] = 0x98badcfe;
	md5->state[3] = 0x10325476;
}

#endif