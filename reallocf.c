/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:58:23 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 17:40:33 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"

void	*reallocf(void *ptr, size_t size)
{
	void	*res;

	write(1, "reallocf\n", 9);
	res = realloc(ptr, size);
	free(ptr);
	return (res);
}
