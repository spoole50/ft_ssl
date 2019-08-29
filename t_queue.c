/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_queue.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoole <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:55:44 by spoole            #+#    #+#             */
/*   Updated: 2019/08/13 12:55:45 by spoole           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			q_print(t_queue *begin)
{
	while (begin != NULL)
	{
		ft_printf("Node# %-2d File?:%-2c String/fileame:%-65s\
		Size(Bits/Bytes/Blocks):%d/%d/%d\n",\
		begin->index, (begin->is_file == TRUE) ? 'Y' : 'N', begin->name,\
		begin->byte_size * 8, begin->byte_size, begin->t_bytes);
		begin = begin->next;
	}
}

void			q_clean(t_queue *begin)
{
	t_queue		*clean;

	clean = begin;
	if (clean == NULL)
		return ;
	while (clean != NULL)
	{
		begin = clean->next;
		free(clean->name);
		if (clean->byte_size != 0)
			free(clean->result);
		free(clean);
		clean = begin;
	}
}

void			queue_add(t_queue **begin, t_queue *temp)
{
	t_queue		*iter;

	iter = *begin;
	if (iter == NULL)
		*begin = temp;
	else
	{
		while (iter->next != NULL)
			iter = iter->next;
		temp->index = iter->index + 1;
		iter->next = temp;
	}
}

void			q_init(t_queue **begin, char *name, int size, int isfile)
{
	t_queue		*temp;
	int			i;
	int			x;

	i = 0;
	x = 0;
	if ((temp = (t_queue*)malloc(sizeof(t_queue))) == NULL)
		err(*begin, "t_queue initialization error");
	temp->index = 1;
	temp->byte_size = size;
	temp->is_file = isfile;
	temp->t_bytes = 0;
	temp->name = ft_strdup(name);
	temp->result = NULL;
	temp->next = NULL;
	queue_add(begin, temp);
}
