/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:56:00 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 10:58:56 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "tools.h"

void	*valloc(size_t size)
{
	void	*ptr;
	
	write(1, "valloc\n", 6);
	ptr = malloc(size);
	ft_bzero(ptr, size);
	return (ptr);
}
