/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:07:21 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 10:44:08 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include <sys/mman.h>

void	free(void *ptr)
{
	write(1, "free\n", 5);
	return ;

	// LOL not good
	munmap(ptr, 42);
}