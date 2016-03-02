/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:30:02 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/02 16:30:10 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_putnbr(int n)
{
	char c;

	if (n >= 10)
		ft_putnbr(n / 10);
	n %= 10;
	c = '0' + n;
	write(1, &c, 1);
}

int		main(void)
{
	int	i;

	write(1, "start\n", 6);
	i = 10000;
	while (--i)
	{
		ft_putnbr(i);
		write(1, "\n", 1);
		malloc(i);
	}
	write(1, "end\n", 4);
	return (0);
}
