/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:05:21 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 15:36:33 by edelangh         ###   ########.fr       */
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

void			*malloc(size_t size)
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
