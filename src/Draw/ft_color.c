/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/31 12:19:41 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

void	ft_color(int nbr, t_data *data)
{
	int	tmp;

	tmp = nbr / 1048576;
	nbr = nbr - 1048576 * tmp;
	data->mlx.r = tmp * 16;
	tmp = nbr / 65536;
	nbr = nbr - 65536 * tmp;
	data->mlx.r += tmp;
	tmp = nbr / 4096;
	nbr = nbr - 4096 * tmp;
	data->mlx.g = tmp * 16;
	tmp = nbr / 256;
	nbr = nbr - 256 * tmp;
	data->mlx.g += tmp;
	tmp = nbr / 16;
	nbr = nbr - 16 * tmp;
	data->mlx.b = tmp * 16;
	data->mlx.b += nbr;
}

void	ft_color_colone(t_data *data, int x, float len, int pcofwall)
{
	int				wall;
	static int		saveface;
	static float	savelen = {0};

	data->y = 0;
	if (pcofwall == 100)
		pcofwall = 99;
	if ((5 < pcofwall && pcofwall < 95) || (fabs(savelen - len) > 0.1))
		saveface = data->face;
	if ((fabs(savelen - len) < 0.4) && ((pcofwall <= 1 && (data->face == 4 || \
data->face == 2)) || (pcofwall >= 98 && (data->face == 1 || data->face == 3))))
		data->face = saveface;
	wall = (data->mlx.winy / 2) + (10 / len) * data->lenwall - \
		((data->mlx.winy / 2) - (10 / len) * data->lenwall);
	if (data->mlx.winy < wall)
		data->y = data->mlx.winy - wall;
	while (data->y < (data->mlx.winy / 2) - (10 / len) * data->lenwall)
		ft_draw(data, x, data->y++, data->sky.color);
	data->nbrpl = data->y;
	while (data->y < (data->mlx.winy / 2) + (10 / len) * data->lenwall)
		ft_draw(data, x, data->y, ft_pixel_of_img(data, data->face, pcofwall, \
				((data->y - data->nbrpl) * 100 / wall)));
	while (data->y < data->mlx.winy)
		ft_draw(data, x, data->y++, data->floor.color);
	savelen = len;
}
