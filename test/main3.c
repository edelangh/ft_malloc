/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 10:35:39 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 14:58:47 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		main(void)
{
	int	i;
   
	i = 1e4;
	srand(time(NULL));
	while (--i)
	{
		free(malloc(rand() % i));
	}
	write(1, "OK\n", 3);
	return (0);
}
