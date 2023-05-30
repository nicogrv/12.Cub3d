/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_id2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/30 11:03:33 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/cub3d.h"

void	ft_init_id_pt6(t_data *data, char **li, char **returnline)
{
	*li = get_next_line(data->fdfile);
	data->ystartmap++;
	*returnline = *li;
}

int	ft_check_name_file(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[--i] != 'b')
		return (1);
	if (str[--i] != 'u')
		return (1);
	if (str[--i] != 'c')
		return (1);
	if (str[--i] != '.')
		return (1);
	return (0);
}
