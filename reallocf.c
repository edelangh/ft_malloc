/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:58:23 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/03 10:08:18 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*reallocf(void *ptr, size_t size)
{
	void	*res;

	res = realloc(ptr, size);
	free(ptr);
	return (res);
}
