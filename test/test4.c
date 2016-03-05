/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 16:52:07 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 17:30:16 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	print(char *s)
{
	write(1, s, strlen(s));
}

int		main()
{
	char	*addr;

	addr = malloc(16);
	free(NULL);
	free(addr + 5);
	if (realloc(addr + 5, 10) == NULL)
		print("Bonjours\n");
	return (0);
}
