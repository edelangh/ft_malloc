/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:16:21 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 14:58:14 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <stddef.h>
# include <unistd.h>
# include <pthread.h>

# define N 32
# define M 128

void				*malloc(size_t size);
void				*calloc(size_t count, size_t size);
void				*valloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *ptr, size_t size);
void				free(void *ptr);

typedef struct		s_hdr t_hdr;

typedef struct		s_hdr
{
	t_hdr			*prev;
	size_t 			size;
	size_t			used;
}					t_hdr;

typedef struct		s_blk
{
	void			*ptr;
	unsigned int	size:31;
	unsigned int	freed:1;
}					t_blk;

typedef struct		s_alloc
{
	t_hdr			*tiny;
	t_hdr			*small;
	t_hdr			*large;
	pthread_mutex_t	mutex;
}					t_alloc;

extern t_alloc		g_alloc;

#define HDR_IS_PLACE(X, S) (X->size - X->used >= S + sizeof(t_blk))
#define FST_BLK(X) (t_blk*)((void*)X + sizeof(t_hdr))
#define HDR_END(X) ((void*)X + X->size)

#define PTR_IN_HDR(X, P) ((char*)P > (char*)X && (void*)P < HDR_END(X))
#endif
