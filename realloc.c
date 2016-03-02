/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:39:55 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 13:29:24 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "tools.h"

static t_blk	*get_blk_by_ptr_bis(t_hdr *hdr, void *ptr)
{
	t_blk	*res;

	res = NULL;
	while (hdr && !res)
	{
		if (PTR_IN_HDR(hdr, ptr))
			res = ptr;
		hdr = hdr->prev;
	}
	return (res);
}

static t_blk	*get_blk_by_ptr(void *ptr)
{
	t_blk	*blk;

	blk = get_blk_by_ptr_bis(g_alloc.tiny, ptr);
	if (!blk)
		blk = get_blk_by_ptr_bis(g_alloc.small, ptr);
	if (!blk)
		blk = get_blk_by_ptr_bis(g_alloc.large, ptr);
	return (blk);
}

void	*realloc(void *ptr, size_t size)
{
	t_blk	*blk;
	void	*new;

	write(1, "realloc\n", 8);
	blk = get_blk_by_ptr(ptr);
	new = malloc(size);
	if (new && ptr && blk)
	{
		ft_memcpy(new, ptr, blk->size);
		free(ptr);
	}
	return (new);
}
