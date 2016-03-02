/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 19:58:54 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 20:08:42 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "tools.h"
#include "alloc.h"

static void	print_all_hdr(t_hdr *hdr)
{
	t_blk	*blk;

	while (hdr)
	{
		ft_putstr("==>");
		ft_putptr(hdr);
		ft_putstr("[");
		ft_putnbr(hdr->used);
		ft_putstr("/");
		ft_putnbr(hdr->size);
		ft_putstr("]");
		ft_putstr("\n");
		blk = FST_BLK(hdr);
		while (blk->size)
		{
			ft_putstr(" -");
			ft_putptr(blk);
			ft_putstr("[");
			ft_putnbr(blk->size);
			ft_putstr("]");
			ft_putstr("->");
			ft_putptr(blk->ptr);
			ft_putstr("\n");
			++blk;
		}
		hdr = hdr->prev;
	}
}

void		ft_print_memory(void)
{
	ft_putstr("==TINY==\n");
	print_all_hdr(g_alloc.tiny);
	ft_putstr("==SMALL==\n");
	print_all_hdr(g_alloc.small);
	ft_putstr("==LARGE==\n");
	print_all_hdr(g_alloc.large);
}
