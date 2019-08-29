/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 01:05:32 by spoole            #+#    #+#             */
/*   Updated: 2019/08/28 01:05:35 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	swap_bits32(uint32_t x)
{
	return ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >> 8)\
	| (((x) & 0x0000ff00) << 8) | (((x) & 0x000000ff) << 24));
}

uint64_t	swap_bits64(uint64_t x)
{
	x = ((x << 8) & 0xFF00FF00FF00FF00ULL)\
	| ((x >> 8) & 0x00FF00FF00FF00FFULL);
	x = ((x << 16) & 0xFFFF0000FFFF0000ULL)\
	| ((x >> 16) & 0x0000FFFF0000FFFFULL);
	return (x << 32) | (x >> 32);
}
