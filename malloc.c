/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:05:21 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 15:11:33 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include <sys/mman.h>

t_alloc	g_alloc = {NULL, NULL, NULL, PTHREAD_MUTEX_INITIALIZER};

static t_hdr	*new_hdr(t_hdr **ahdr, size_t sz)
{
	t_hdr	*prev;
	t_hdr	*hdr;
	t_blk	*blk;
	size_t	page_sz;

	prev = *ahdr;
	page_sz = getpagesize();
	if (sz <= M)
		sz *= 100;
	sz = (((sz + sizeof(t_blk) * 2 + sizeof(t_hdr)) / page_sz) + 1) * page_sz;
	hdr = mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	*ahdr = hdr;
	hdr->prev = prev;
	hdr->size = sz;
	hdr->used = sizeof(t_hdr) + sizeof(t_blk);
	blk = (void*)hdr + sizeof(t_hdr);
	blk->size = 0;
	blk->freed = 0;
	return (hdr);
}

static int		hdr_is_realy_place(t_hdr *hdr, size_t size)
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

static t_hdr	*get_hdr(t_hdr **ahdr, size_t size)
{
	t_hdr		*hdr;

	hdr = *ahdr;
	while (hdr && !(HDR_IS_PLACE(hdr, size) && hdr_is_realy_place(hdr, size)))
		hdr = hdr->prev;
	if (!hdr)
		hdr = new_hdr(ahdr, size);
	return (hdr);
}

static size_t	get_freed_size(t_blk *blk)
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

static void		fix_de_merde(t_blk *blk, size_t move)
{
	t_blk	*tmp;

	while (blk->size)
	{
		tmp = blk + move;
		blk->size = tmp->size;
		blk->freed = tmp->freed;
		blk->ptr = tmp->ptr;
		++blk;
	}
}

static t_blk	*use_freed(t_hdr *hdr, t_blk *blk, size_t size, void *ptr)
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
	fix_de_merde(blk, ((void*)tblk - (void*)blk) / sizeof(t_blk));
	blk->size = freed;
	blk->freed = 0;
	blk->ptr = ptr;
	hdr->used += blk->size + sizeof(t_blk);
	return (blk);
}

static t_blk	*new_blk(t_hdr *hdr, size_t size)
{
	t_blk	*blk;
	t_blk	*tmp;
	void	*ptr;

	blk = FST_BLK(hdr);
	ptr = HDR_END(hdr);
	while (blk->size != 0)
	{
		ptr = blk->ptr;
		if (get_freed_size(blk) >= size)
			return (use_freed(hdr, blk, size, ptr));
		++blk;
	}
	ptr -= size;
	blk->size = size;
	blk->freed = 0;
	blk->ptr = ptr;
	hdr->used += size + sizeof(t_blk);
	tmp = blk + 1;
	tmp->size = 0;
	tmp->freed = 0;
	return (blk);
}

static void		*get_alloc(t_hdr **ahdr, size_t size)
{
	t_blk	*blk;
	t_hdr	*hdr;
	void	*ptr;

	hdr = get_hdr(ahdr, size);
	blk = new_blk(hdr, size);
	ptr = blk->ptr;
	return (ptr);
}

void	*malloc(size_t size)
{
	void	*ptr;

	if (!size)
		return (NULL);
	pthread_mutex_lock(&(g_alloc.mutex));
	if (size <= N)
		ptr = get_alloc(&(g_alloc.tiny), size);
	else if (size <= M)
		ptr = get_alloc(&(g_alloc.small), size);
	else
		ptr = get_alloc(&(g_alloc.large), size);
	pthread_mutex_unlock(&(g_alloc.mutex));
	return (ptr);
}
