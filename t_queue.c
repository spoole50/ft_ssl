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

void			cleanQ(t_queue *begin)
{
	t_queue		*clean;

	clean = begin;
	if (clean == NULL)
		return ;
	while (clean != NULL)
	{
		begin = clean->next;
		free(clean->name);
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

void			q_init(t_queue **begin, char *name, int size, int _is_file)
{
	t_queue 	*temp;

	if ((temp = (t_queue*)malloc(sizeof(t_queue))) == NULL)
		err(*begin, "t_queue initialization error");
	temp->index = 1;
	temp->bit_size = size * 8;
	temp->is_file = _is_file;
	temp->name = ft_strdup(name);
	temp->next = NULL;
	queue_add(begin, temp);
}