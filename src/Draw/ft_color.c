/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/14 16:00:25 by ngriveau         ###   ########.fr       */
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

void	ft_color_colone_pt2(t_data *d, int x, float len, float pcofwall)
{
	if (d->y < 0)
		d->y = 0;
	while (d->y < (d->mlx.winy / 2) + (10 / len) * d->lenwall && \
d->y < d->mlx.winy + 10)
		ft_draw(d, x, d->y, \
ft_pixel_of_img(d, d->face, pcofwall, (d->y - d->nbrpl) * 100 / d->wall));
	while (d->y < d->mlx.winy)
		ft_draw(d, x, d->y++, d->floor.color);
}

void	ft_color_colone(t_data *d, int x, float len, float pcofwall)
{
	static int		saveface;
	static float	savelen = {0};

	d->y = 0;	
	if ((fabs(savelen - len) < 0.4) && ((pcofwall <= 1 && (d->face == 4 || \
d->face == 2)) || (pcofwall >= 98 && (d->face == 1 || d->face == 3))))
		d->face = saveface;
	if ((5 < pcofwall && pcofwall < 95) || (fabs(savelen - len) > 0.1))
		saveface = d->face;
	d->wall = (d->mlx.winy / 2) + (10 / len) * d->lenwall - \
		((d->mlx.winy / 2) - (10 / len) * d->lenwall);
	if (d->mlx.winy < d->wall)
		d->y = d->mlx.winy - d->wall;
	while (d->y < (d->mlx.winy / 2) - (10 / len) * d->lenwall && \
0 < (d->mlx.winy / 2) - (10 / len) * d->lenwall)
		ft_draw(d, x, d->y++, d->sky.color);
	d->nbrpl = (d->mlx.winy / 2) - (10 / len) * d->lenwall;
	ft_color_colone_pt2(d, x, len, pcofwall);
	savelen = len;
}
