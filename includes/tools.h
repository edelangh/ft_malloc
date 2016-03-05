/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:13:38 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 17:58:33 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <stddef.h>

typedef struct s_blk	t_blk;
typedef struct s_hdr	t_hdr;

typedef struct			s_ptr_info
{
	t_hdr				*hdr;
	t_hdr				**ahdr;
	t_blk				*blk;
	void				*ptr;
}						t_ptr_info;

void					*ft_bzero(void *ptr, size_t size);
void					*ft_memcpy(void *dst, void *src, size_t size);
t_ptr_info				get_ptr_info(void *ptr);
void					ft_print_memory(void);
void					show_alloc_mem(void);
size_t					get_alloc_size(void *ptr);

void					ft_putptr(void *s);
void					ft_putnbr(size_t s);
void					ft_putstr(const char *s);
#endif
