/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 16:52:07 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 17:06:41 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define M (1024*1024)

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main()
{
	char	*addr1;
	char	*addr3;

	addr1 = malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print(addr3);
	return (0);
}
