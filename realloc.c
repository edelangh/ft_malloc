/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:39:55 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 18:17:56 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "tools.h"

void	*realloc(void *ptr, size_t size)
{
	t_blk		*blk;
	void		*new;
	t_ptr_info	i;

	pthread_mutex_lock(&(g_alloc.mutex2));
	i = get_ptr_info(ptr);
	blk = i.blk;
	new = NULL;
	if (!blk || (blk && blk->size <= size))
		new = malloc(size);
	if (new && ptr && blk)
	{
		ft_memcpy(new, ptr, blk->size);
		pthread_mutex_unlock(&(g_alloc.mutex2));
		free(ptr);
		pthread_mutex_lock(&(g_alloc.mutex2));
	}
	pthread_mutex_unlock(&(g_alloc.mutex2));
	return (new);
}
