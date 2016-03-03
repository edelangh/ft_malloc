/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 10:35:39 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/03 14:51:31 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		main(void)
{
	int	i = 1e5;

	srand(time(NULL));
	while (--i)
	{
		malloc(rand() % i);
	}
	write(1, "OK\n", 3);
	sleep(5);
	return (0);
}
