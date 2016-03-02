/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:14:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 17:15:54 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

#include <unistd.h>
void	ft_putnbr(size_t size)
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
void	ft_putptr(void *ptr)
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
