/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:30:02 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 13:32:04 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		main(void)
{
	int	i;

	write(1, "start\n", 6);
	i = 10000;
	while (--i)
		malloc(i);
	write(1, "end\n", 4);
	return (0);
}
