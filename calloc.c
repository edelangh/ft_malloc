/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:12:36 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 17:43:15 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "tools.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&(g_alloc.mutex2));
	if (size > 0 && count > (~(size_t)0) / size)
		return (NULL);
	size = count * size;
	ptr = malloc(size);
	ft_bzero(ptr, size);
	pthread_mutex_unlock(&(g_alloc.mutex2));
	return (ptr);
}
