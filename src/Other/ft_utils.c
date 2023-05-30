/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/30 11:14:44 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/cub3d.h"

int	is_ws(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_player(int c)
{
	if (c == 2 || c == 3 || c == 4 || c == 5)
		return (1);
	return (0);
}

int	ft_is_wc_or_new_line(char *line)
{
	int	i;

	i = 0;
	while (is_ws(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}
