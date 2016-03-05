/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:39:55 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 14:51:49 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "tools.h"

void	*realloc(void *ptr, size_t size)
{
	t_blk		*blk;
	void		*new;
	t_ptr_info	i;

	i = get_ptr_info(ptr);
	blk = i.blk;
	new = malloc(size);
	if (new && ptr && blk)
	{
		ft_memcpy(new, ptr, blk->size);
		free(ptr);
	}
	return (new);
}
