/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 19:58:54 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 14:56:37 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "tools.h"
#include "alloc.h"

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

static void		print_all_hdr(t_hdr *hdr)
{
	t_blk	*blk;
	size_t	real_size;
	void	*prev;
	size_t	diff;

	while (hdr)
	{
		real_size = sizeof(t_hdr) + sizeof(t_blk);
		prev = HDR_END(hdr);
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
			if (blk->freed == 0)
				real_size += blk->size + sizeof(t_blk);
			ft_putstr(" -");
			ft_putptr(blk);
			ft_putstr("[");
			ft_putnbr(blk->size);
			ft_putstr("]");
			ft_putstr("{");
			ft_putnbr(get_freed_size(blk));
			ft_putstr("}");
			ft_putstr("->");
			ft_putptr(blk->ptr);
			ft_putstr(" + ");
			diff = (size_t)(prev - blk->ptr);
			ft_putnbr(diff);
			if (diff != blk->size)
				ft_putstr(" -- ERROR Detected");
			ft_putstr("\n");
			prev = blk->ptr;
			++blk;
		}
		ft_putstr("RealSize:");
		ft_putnbr(real_size);
		if (real_size != hdr->used)
			ft_putstr(" -- ERROR Detected");
		ft_putstr("\n");
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

void		ft_putnbr(size_t size)
{
	size_t	n;
	char	c;

	n = (size_t)size;
	if (n >= 10)
		ft_putnbr(n / 10);
	n %= 10;
	c = '0' + n;
	write(1, &c, 1);
}

void		ft_putptr(void *ptr)
{
	size_t	n;
	char	c;

	n = (size_t)ptr;
	if (n >= 16)
		ft_putptr((void*)(n / 16));
	else
		write(1, "0x", 2);
	n %= 16;
	if (n >= 10)
		c = 'a' + n - 10;
	else
		c = '0' + n;
	write(1, &c, 1);
}

void		ft_putstr(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		++i;
	write(1, s, i);
}
