/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:13:38 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 17:15:04 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

#include <stddef.h>

void	ft_putptr(void *ptr); // LOL
void	ft_putnbr(size_t size);

void	*ft_bzero(void *ptr, size_t size);
void	*ft_memcpy(void *dst, void *src, size_t size);

#endif
