/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 19:58:54 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 15:51:32 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "tools.h"
#include "alloc.h"

static void		print_all_hdr(t_hdr *hdr)
{
	t_blk	*blk;

	while (hdr)
	{
		printf("==> %p[%zu/%zu]\n", hdr, hdr->used, hdr->size);
		blk = FST_BLK(hdr);
		while (blk->size)
		{
			if (blk->freed == 0)
				real_size += blk->size + sizeof(t_blk);
			printf("\t-%p[%zu]{%zu}->%p\n",
					blk, blk->size, get_freed_size(blk), blk->ptr);
			++blk;
		}
		hdr = hdr->prev;
	}
}

void			ft_print_memory(void)
{
	printf("== TINY ==\n");
	print_all_hdr(g_alloc.tiny);
	printf("== SMALL ==\n");
	print_all_hdr(g_alloc.small);
	printf("== LARGE ==\n");
	print_all_hdr(g_alloc.large);
}
