/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 16:52:07 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 17:02:29 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		main()
{
	int	i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	return (0);
}
