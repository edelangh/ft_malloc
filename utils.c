/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 15:31:58 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 15:36:09 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

size_t		get_freed_size(t_blk *blk)
{
	size_t size;

	size = 0;
	while (blk->freed && blk->size)
	{
		size += blk->size;
		++blk;
	}
	return (size);
}

static void	rm_blk(t_blk *blk, size_t count)
{
	t_blk	*tmp;

	while (blk->size)
	{
		tmp = blk + count;
		blk->size = tmp->size;
		blk->freed = tmp->freed;
		blk->ptr = tmp->ptr;
		++blk;
	}
}

t_blk		*use_freed(t_hdr *hdr, t_blk *blk, size_t size, void *ptr)
{
	t_blk	*tblk;
	size_t	freed;

	freed = blk->size;
	tblk = blk;
	while (freed < size)
	{
		++tblk;
		ptr = tblk->ptr;
		freed += tblk->size;
	}
	rm_blk(blk, ((void*)tblk - (void*)blk) / sizeof(t_blk));
	blk->size = freed;
	blk->freed = 0;
	blk->ptr = ptr;
	hdr->used += blk->size + sizeof(t_blk);
	return (blk);
}

int			hdr_is_realy_place(t_hdr *hdr, size_t size)
{
	t_blk	*blk;
	size_t	free_size;

	free_size = hdr->size - sizeof(t_hdr) - sizeof(t_blk);
	blk = FST_BLK(hdr);
	while (blk->size)
	{
		if (blk->freed && blk->size >= size)
			return (1);
		free_size -= blk->size + sizeof(t_blk);
		++blk;
	}
	return (free_size >= size + sizeof(t_blk));
}
