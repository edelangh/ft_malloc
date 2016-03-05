/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:07:21 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 18:18:01 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "tools.h"
#include <sys/mman.h>

void	free_hdr(t_hdr **ahdr, t_hdr *hdr)
{
	t_hdr	*tmp;
	t_hdr	*ptr;

	ptr = *ahdr;
	tmp = NULL;
	while (ptr != hdr)
	{
		tmp = ptr;
		ptr = ptr->prev;
	}
	if (!tmp)
		*ahdr = NULL;
	else
		tmp->prev = hdr->prev;
	munmap(hdr, hdr->size);
}

void	free(void *ptr)
{
	t_hdr		*hdr;
	t_blk		*blk;
	t_ptr_info	i;

	pthread_mutex_lock(&(g_alloc.mutex2));
	if (ptr)
	{
		i = get_ptr_info(ptr);
		blk = i.blk;
		hdr = i.hdr;
		if (blk && blk->freed == 0 && blk->ptr == ptr)
		{
			hdr->used -= blk->size + sizeof(t_blk);
			blk->freed = 1;
			if (hdr->used == sizeof(t_hdr) + sizeof(t_blk))
				free_hdr(i.ahdr, i.hdr);
			else if ((blk + 1)->size == 0)
			{
				blk->size = 0;
				blk->freed = 0;
			}
		}
	}
	pthread_mutex_unlock(&(g_alloc.mutex2));
}
