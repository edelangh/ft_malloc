/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 19:58:54 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 16:47:48 by edelangh         ###   ########.fr       */
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
			printf("\t-%p[%d]{%zu}->%p\n",
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

void			ft_putnbr(size_t size)
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

void			ft_putptr(void *ptr)
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
		c = 'A' + n - 10;
	else
		c = '0' + n;
	write(1, &c, 1);
}

void			ft_putstr(const char *s)
{
	int		i;

	i = 0;
	while (s[i])
		++i;
	write(1, s, i);
}
