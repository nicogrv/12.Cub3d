/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/09 00:09:59 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

void	ft_verif_ok_map_pt3(t_data *data)
{
	data->playerx = data->x + 0.5;
	data->playery = data->y + 0.5;
	if (data->map[data->y][data->x] == 2)
		data->playerr = 90;
	if (data->map[data->y][data->x] == 3)
		data->playerr = 180;
	if (data->map[data->y][data->x] == 4)
		data->playerr = 270;
	if (data->map[data->y][data->x] == 5)
		data->playerr = 0;
	printf(LIGHTPURPLE"■"NC);
	data->map[data->y][data->x] = 0;
	data->nbrpl++;
}

void	ft_verif_ok_map_pt2(t_data *data)
{
	if (data->map[data->y][data->x] == 1)
		printf(LIGHTRED"■"NC);
	else if (data->map[data->y][data->x] == 0)
		printf(LIGHTGREEN"■"NC);
	else if (data->map[data->y][data->x] == 7)
		printf(" ");
	if (is_player(data->map[data->y][data->x]))
		ft_verif_ok_map_pt3(data);
}

int	ft_verif_ok_map(t_data *data)
{
	data->x = -1;
	data->y = -1;
	data->nbrpl = 0;
	while (++data->y < data->mapy)
	{
		while (++data->x < data->mapx)
		{
			if ((data->y == 0 || data->x == 0 || data->y == data->mapy -1 || \
data->x == data->mapx -1) && (data->map[data->y][data->x] == 0 || \
is_player(data->map[data->y][data->x])))
				return (ft_free_map(data, -42), printf(RED"Incorrect Map\n"NC));
			if ((data->map[data->y][data->x] == 0 || \
is_player(data->map[data->y][data->x])) && (\
data->map[data->y -1][data->x] == 7 || data->map[data->y +1][data->x] == 7 || \
data->map[data->y][data->x -1] == 7 || data->map[data->y][data->x +1] == 7))
				return (ft_free_map(data, -42), printf(RED"Incorrect Map\n"NC));
			ft_verif_ok_map_pt2(data);
		}
		printf("\n");
		data->x = -1;
	}
	if (data->nbrpl != 1)
		return (ft_free_map(data, -42), \
				printf(RED"Incorrect Number Player\n"NC));
	return (0);
}
