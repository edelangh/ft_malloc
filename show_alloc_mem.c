/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 16:37:35 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 17:48:50 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "tools.h"

size_t		show_alloc_mem2(const char *t, t_hdr *hdr)
{
	t_blk	*blk;
	t_blk	*first;
	size_t	res;

	ft_putstr(t);
	ft_putptr(hdr);
	ft_putstr("\n");
	blk = FST_BLK(hdr);
	first = blk;
	res = 0;
	while (blk->size)
		++blk;
	while (blk != first)
	{
		--blk;
		ft_putptr(blk->ptr);
		ft_putstr(" - ");
		ft_putptr(blk->ptr + blk->size);
		ft_putstr(" : ");
		ft_putnbr(blk->size);
		ft_putstr(" octets\n");
		res += blk->size;
	}
	return (res);
}

static void	print(size_t res)
{
	ft_putstr("Total : ");
	ft_putnbr(res);
	ft_putstr(" octets\n");
}

void		show_alloc_mem(void)
{
	t_hdr	*hdr;
	size_t	res;

	res = 0;
	pthread_mutex_lock(&(g_alloc.mutex2));
	hdr = g_alloc.tiny;
	while (hdr)
	{
		res += show_alloc_mem2("TINY : ", hdr);
		hdr = hdr->prev;
	}
	hdr = g_alloc.small;
	while (hdr)
	{
		res += show_alloc_mem2("SMALL : ", hdr);
		hdr = hdr->prev;
	}
	hdr = g_alloc.large;
	while (hdr)
	{
		res += show_alloc_mem2("LARGE : ", hdr);
		hdr = hdr->prev;
	}
	print(res);
	pthread_mutex_unlock(&(g_alloc.mutex2));
}
