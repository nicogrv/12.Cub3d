/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:27:41 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/03 19:24:21 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"



int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_mode(const char *str, int mode)
{
	int	i;

	i = 0;
	while (str && str[i] && mode == 0)
		i++;
	while (str && str[i] && mode == 1 && str[i] != '\n')
		i++;
	while (str && str[i] && mode == 2 && str[i] != ',' && str[i] != ' ' && str[i] != '\n')
		i++;
	while (str && str[i] && mode == 3 && str[i] != '\n' && str[i] != ' ')
		i++;
	return (i);
}
