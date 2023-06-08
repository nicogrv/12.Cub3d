/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_0_360.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/08 23:35:17 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

void	ft_ray_270_360(t_data *d)
{
	d->ax -= 270;
	if (d->ax == 0)
		d->ax = 0.1;
	d->hyv = (1 - (d->posy - (int)d->posy)) / cos(d->ax / RAD);
	d->hyr = ((d->posx - (int)d->posx)) / cos((90 - d->ax) / RAD);
	if (d->hyv < d->hyr)
	{
		d->decaly = (1 - (d->posy - (int)d->posy)) + 0.000001;
		d->decalx = ((1 - (d->posy - (int)d->posy)) * -1) * \
						tan((d->ax) / RAD) + 0.000001 ;
		d->length += d->hyv;
		d->face = 3;
		d->pcofwall = 100 - ((int)((d->posx + d->decalx - \
						(int)(d->posx + d->decalx)) * 100));
	}
	else
	{
		d->decaly = (d->posx - (int)d->posx) * tan((90 - d->ax) / RAD) - 0.000001;
		d->decalx = ((d->posx - (int)d->posx) * -1) - 0.000001;
		d->length += d->hyr;
		d->face = 4;
		d->pcofwall = 100 - ((int)((d->posy + d->decaly - \
					(int)(d->posy + d->decaly)) * 100));
	}
	d->ax += 270;
}

void	ft_ray_180_270(t_data *d)
{
	d->ax -= 180;
	if (d->ax == 0)
		d->ax = 0.1;
	d->hyv = (1 - (d->posy - (int)d->posy)) / cos((90 - d->ax) / RAD);
	d->hyr = (1 - (d->posx - (int)d->posx)) / cos(d->ax / RAD);
	if (d->hyv < d->hyr)
	{
		d->decaly = (1 - (d->posy - (int)d->posy)) + 0.000001;
		d->decalx = (1 - (d->posy - (int)d->posy)) * \
				tan((90 - d->ax) / RAD) + 0.000001;
		d->length += d->hyv;
		d->face = 3;
		d->pcofwall = 100 - ((int)((d->posx + d->decalx - \
				(int)(d->posx + d->decalx)) * 100));
	}
	else
	{
		d->decaly = (1 - (d->posx - (int)d->posx)) * tan((d->ax) / RAD) + 0.000001;
		d->decalx = (1 - (d->posx - (int)d->posx)) + 0.000001;
		d->length += d->hyr ;
		d->face = 2;
		d->pcofwall = (int)((d->posy + d->decaly - \
						(int)(d->posy + d->decaly)) * 100);
	}
	d->ax += 180;
}

void	ft_ray_90_180(t_data *d)
{
	d->ax -= 90;
	if (d->ax == 0)
		d->ax = 0.1;
	d->hyv = (d->posy - (int)d->posy) / cos(d->ax / RAD);
	d->hyr = (1 - (d->posx - (int)d->posx)) / cos((90 - d->ax) / RAD);
	if (d->hyv < d->hyr)
	{
		d->decaly = ((d->posy - (int)d->posy) * -1) - 0.000001;
		d->decalx = (d->posy - (int)d->posy) * tan((d->ax) / RAD) - 0.000001;
		d->length += d->hyv;
		d->face = 1;
		d->pcofwall = (int)((d->posx + d->decalx - \
				(int)(d->posx + d->decalx)) * 100);
	}
	else
	{
		d->decaly = ((1 - (d->posx - (int)d->posx)) * -1) * \
				tan((90 - d->ax) / RAD) + 0.000001;
		d->decalx = (1 - (d->posx - (int)d->posx)) + 0.000001;
		d->length += d->hyr;
		d->face = 2;
		d->pcofwall = (int)((d->posy + d->decaly - \
				(int)(d->posy + d->decaly)) * 100);
	}
	d->ax += 90;
}

void	ft_ray_0_90_pt2(t_data *d)
{
	if (d->hyv < d->hyr)
	{
		d->decaly = ((d->posy - (int)d->posy) * -1) - 0.000001;
		d->decalx = ((d->posy - (int)d->posy) * -1) * \
						tan((90 - d->ax) / RAD) - 0.00001;
		d->length += d->hyv;
		d->face = 1;
		d->pcofwall = (int)((d->posx + d->decalx - \
						(int)(d->posx + d->decalx)) * 100);
	}
	else
	{
		d->decaly = ((d->posx - (int)d->posx) * -1) * \
						tan((d->ax) / RAD) - 0.000001;
		d->decalx = ((d->posx - (int)d->posx) * -1) - 0.000001;
		d->length += d->hyr;
		d->face = 4;
		d->pcofwall = 100 - ((int)((d->posy + d->decaly - \
					(int)(d->posy + d->decaly)) * 100));
	}

}

void	ft_ray_0_90(t_data *d)
{
	if (d->ax == 0)
		d->ax = 0.1;
	if (d->ax == 90)
		d->ax = 89.9;
	d->hyv = (d->posy - (int)d->posy) / cos(((90 - d->ax) / RAD));
	d->hyr = (d->posx - (int)d->posx) / cos(d->ax / RAD);
	if (d->hyv < -5)
		d->hyv = 5;
	ft_ray_0_90_pt2(d);
}
