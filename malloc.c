/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:05:21 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 13:45:31 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include <sys/mman.h>

t_alloc	g_alloc = {NULL, NULL, NULL};

static t_hdr	*new_hdr(t_hdr** ahdr, size_t size)
{
	t_hdr	*prev;
	t_hdr	*hdr;
	t_blk	*blk;

	prev = *ahdr;
	(void)size;
	write(1, "-mmap", 4);
	hdr = mmap(NULL, 4096, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_ANON|MAP_SHARED, -1, 0);
	*ahdr = hdr;
	hdr->prev = prev;
	hdr->size = 4096;
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
	while (hdr && !HDR_IS_PLACE(hdr, size))
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

	write(1, "-1", 2);
	blk = FST_BLK(hdr);
	ptr = HDR_END(hdr);
	write(1, "-2", 2);
	while (blk->size != 0)
	{
		ptr = blk->ptr;
		++blk;
	}
	// Set blk
	ptr -= size;
	blk->size = size;
	blk->freed = 0;
	write(1, "-3", 2);
	blk->ptr = ptr;
	write(1, "-4", 2);
	// INIT next
	hdr->used += size + sizeof(t_blk);
	tmp = blk + 1;
	tmp->size = 0;
	tmp->freed = 0;
	write(1, "-5", 2);
	return (blk);
}

static void		*get_alloc(t_hdr **ahdr, size_t size)
{
	t_blk	*blk;
	t_hdr	*hdr;
	void	*ptr;

	write(1, "-a", 2);
	hdr = get_hdr(ahdr, size);
	// TODO defrag
	write(1, "-b", 2);
	blk = new_blk(hdr, size);
	write(1, "-c", 2);
	ptr = blk->ptr;
	return (ptr);
}

void	*malloc(size_t size)
{
	void	*ptr;

	write(1, "malloc", 6);
	if (size <= N)
		ptr = get_alloc(&(g_alloc.tiny), size);
	else if (size <= M)
		ptr = get_alloc(&(g_alloc.small), size);
	else
		ptr = get_alloc(&(g_alloc.large), size);
	write(1, "-OK\n", 4);
	return (ptr);
}
