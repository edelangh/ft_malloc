/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:14:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/03 11:20:23 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "alloc.h"
#include <unistd.h>

static void		get_blk_by_ptr_bis(t_hdr *hdr, void *ptr, t_ptr_info *i)
{
	t_blk	*blk;

	blk = NULL;
	while (hdr && !blk)
	{
		if (PTR_IN_HDR(hdr, ptr))
		{
			i->hdr = hdr;
			blk = FST_BLK(hdr);
			while (blk->ptr != ptr)
				++blk;
			i->blk = blk;
			if (!PTR_IN_HDR(hdr, blk) || (void*)blk > ptr) // TODO RM this check
			{
				if (!PTR_IN_HDR(hdr, blk))
					ft_putstr("BLK DE MERDE\n");
				else
					ft_putstr("BLK DE MER2\n");
				while (1)
					continue ;
			}
		}
		hdr = hdr->prev;
	}
}

t_ptr_info		get_ptr_info(void *ptr)
{
	t_ptr_info	i;

	i.hdr = NULL;
	i.blk = NULL;
	i.ptr = ptr;
	i.ahdr = &g_alloc.tiny;
	get_blk_by_ptr_bis(g_alloc.tiny, ptr, &i);
	if (!i.blk)
	{
		i.ahdr = &g_alloc.small;
		get_blk_by_ptr_bis(g_alloc.small, ptr, &i);
	}
	if (!i.blk)
	{
		i.ahdr = &g_alloc.large;
		get_blk_by_ptr_bis(g_alloc.large, ptr, &i);
	}
	return (i);
}

void	*ft_memcpy(void *dst, void *src, size_t size)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	size_t			i;

	if (src && dst)
	{
		i = 0;
		cdst = dst;
		csrc = src;
		while (i < size)
		{
			cdst[i] = csrc[i];
			++i;
		}
	}
	return (dst);
}

void	*ft_bzero(void *ptr, size_t size)
{
	size_t			i;
	unsigned char	*cptr;

	i = 0;
	if (ptr)
	{
		cptr = ptr;
		while (i < size)
		{
			cptr[i] = 0;
			++i;
		}
	}
	return (ptr);
}
