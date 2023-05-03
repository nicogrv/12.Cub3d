/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:05:14 by ngriveau          #+#    #+#             */
/*   Updated: 2022/11/29 10:29:22 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_dup_upligne(char *upligne, char *buffer, int i, int j)
{
	int	size;

	size = ft_s(&buffer[i], 1);
	while (--size + 1)
	{
		upligne[j] = buffer[i];
		buffer[i] = -42;
		i++;
		j++;
	}
	i = 0;
	while (upligne[i] != '\0')
	{
		if (upligne[i] == -42)
			upligne[i] = '\0';
		i++;
	}
	return (upligne);
}
