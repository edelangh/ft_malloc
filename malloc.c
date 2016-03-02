/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:05:21 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 20:53:26 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include <sys/mman.h>

t_alloc	g_alloc = {NULL, NULL, NULL, PTHREAD_MUTEX_INITIALIZER};


#include <signal.h> // NOP
#include <stdlib.h> // NOP
#include <errno.h>

void	perror(const char *s); // NOP

static t_hdr	*new_hdr(t_hdr** ahdr, size_t size)
{
	t_hdr	*prev;
	t_hdr	*hdr;
	t_blk	*blk;
	size_t	page_size;

	prev = *ahdr;
	write(2, "-mmap", 4);
	page_size = getpagesize();
	size = (((size + sizeof(t_blk) * 2 + sizeof(t_hdr)) / page_size) + 1) * page_size;
	hdr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, (off_t)0);
	if (hdr == MAP_FAILED)
	{
		write(2, "PUTAIN\n", 7);
		perror("signal-error");
		while (1)
			continue ;
	}
	*ahdr = hdr;
	hdr->prev = prev;
	hdr->size = size;
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
	if (hdr)
	{
		write(2, "-", 1);
		ft_putnbr(hdr->size);
		write(2, "-", 1);
		ft_putnbr(hdr->used);
	}
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

	blk = FST_BLK(hdr);
	ptr = HDR_END(hdr);
	while (blk->size != 0)
	{
		ptr = blk->ptr;
		++blk;
	}
	// Set blk
	ptr -= size;
	blk->size = size;
	blk->freed = 0;
	write(2, "-3", 2);
	blk->ptr = ptr;
	write(2, "-4", 2);
	// INIT next
	hdr->used += size + sizeof(t_blk);
	tmp = blk + 1;
	tmp->size = 0;
	tmp->freed = 0;
	return (blk);
}

static void		*get_alloc(t_hdr **ahdr, size_t size)
{
	t_blk	*blk;
	t_hdr	*hdr;
	void	*ptr;

	hdr = get_hdr(ahdr, size);
	// TODO defrag
	blk = new_blk(hdr, size);
	ptr = blk->ptr;
	return (ptr);
}

void		lol(int sig) // NOP
{
	static int a = 1;

	if (a)
	{
		a = 0;
	write(2, "SIGNAL:", 7);
	ft_putnbr(sig);
	write(2, "\n", 1);
	perror("signal-error");
	ft_print_memory();
	}
	exit(1);
}

void	*malloc(size_t size)
{
	void	*ptr;

	static int a = 1;
	if (a)
	{
		a = 0;
		int i;
		for (i = 1; i < 22; ++i)
			signal(i, &lol);
	}
	pthread_mutex_lock(&(g_alloc.mutex));
	errno = 0;
	write(2, "malloc", 6);
	write(2, "-", 1);
	ft_putnbr(size);
	if (size <= N)
		ptr = get_alloc(&(g_alloc.tiny), size);
	else if (size <= M)
		ptr = get_alloc(&(g_alloc.small), size);
	else
		ptr = get_alloc(&(g_alloc.large), size);
	write(2, "-", 1);
	ft_putptr(ptr);
	write(2, "-OK\n", 4);
	pthread_mutex_unlock(&(g_alloc.mutex));
	return (ptr);
}
