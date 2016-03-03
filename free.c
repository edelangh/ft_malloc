/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:07:21 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/03 20:35:55 by edelangh         ###   ########.fr       */
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

	ft_putstr("free");
	if (ptr)
	{
		i = get_ptr_info(ptr);
		blk = i.blk;
		hdr = i.hdr;
		if (blk)
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
		else
		{
		/*	ft_putstr("Erreur free:");
			ft_putptr(ptr);
			write(1, "\n", 1);
		*/
		}
	}
	ft_putstr("-out\n");
}
