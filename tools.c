/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:14:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 11:03:50 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

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
