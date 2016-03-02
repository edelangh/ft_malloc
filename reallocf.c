/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:58:23 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 10:58:43 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*reallocf(void *ptr, size_t size)
{
	write(1, "reallocf\n", 9);
	(void)size;
	free(ptr);
	return (ptr);
}
