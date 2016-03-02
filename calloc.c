/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:12:36 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 10:43:46 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "tools.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	// TODO Check if not overflow
	size = count * size;
	write(1, "calloc\n", 6);
	ptr = malloc(size);
	ft_bzero(ptr, size);
	return (ptr);
}
