/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/14 15:20:34 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

void	ft_draw(t_data *data, float x, float y, int color)
{
	unsigned long	pixel;

	x = roundf(x);
	y = roundf(y);
	ft_color(color, data);
	pixel = (y * data->mlx.size) + (x * 4);
	if (((unsigned long)(data->mlx.size) * data->mlx.winy) < pixel - 5 || x <= 0
		|| y <= 0 || y > data->mlx.winy || x > data->mlx.winx)
		return ;
	if (data->mlx.e == 1)
	{
		data->mlx.data[pixel + 0] = 0;
		data->mlx.data[pixel + 1] = data->mlx.r;
		data->mlx.data[pixel + 2] = data->mlx.g;
		data->mlx.data[pixel + 3] = data->mlx.b;
	}
	else if (data->mlx.e == 0)
	{
		data->mlx.data[pixel + 0] = data->mlx.b;
		data->mlx.data[pixel + 1] = data->mlx.g;
		data->mlx.data[pixel + 2] = data->mlx.r;
		data->mlx.data[pixel + 3] = 0;
	}
}

void	ft_draw_mini(t_data *data, float x, float y, int color)
{
	unsigned long	pixel;

	x = roundf(x);
	y = roundf(y);
	ft_color(color, data);
	pixel = (y * data->mini.img.size) + (x * 4);
	if (data->mini.img.e == 1)
	{
		data->mini.img.data[pixel + 0] = 1;
		data->mini.img.data[pixel + 1] = data->mlx.r;
		data->mini.img.data[pixel + 2] = data->mlx.g;
		data->mini.img.data[pixel + 3] = data->mlx.b;
	}
	else if (data->mini.img.e == 0)
	{
		data->mini.img.data[pixel + 0] = data->mlx.b;
		data->mini.img.data[pixel + 1] = data->mlx.g;
		data->mini.img.data[pixel + 2] = data->mlx.r;
		data->mini.img.data[pixel + 3] = 1;
	}
}

void	ft_pixel_of_img_2(t_data *data, int face, float pcofwall, float y)
{
	int	pixel;
	int	x;

	if (face == 3)
	{
		x = data->south.width * ((float)pcofwall / 100);
		y = data->south.height * ((float)y / 100);
		pixel = ((int)y * data->south.img.size) + (x * 4);
		data->mlx.r = data->south.img.data[pixel + 2];
		data->mlx.g = data->south.img.data[pixel + 1];
		data->mlx.b = data->south.img.data[pixel + 0];
	}
	if (face == 4)
	{
		x = data->west.width * ((float)pcofwall / 100);
		y = data->west.height * ((float)y / 100);
		pixel = ((int)y * data->west.img.size) + (x * 4);
		data->mlx.r = data->west.img.data[pixel + 2];
		data->mlx.g = data->west.img.data[pixel + 1];
		data->mlx.b = data->west.img.data[pixel + 0];
	}
}

void	ft_round_data(float *pcofwall, float *y)
{
	if (*y < 0)
		*y = 0;
	if (99 < *y)
		*y = 99;
	if (*pcofwall < 0)
		*pcofwall = 0;
	if (100 <= *pcofwall)
		*pcofwall = 99.9;
}

int	ft_pixel_of_img(t_data *data, int face, float pcofwall, float y)
{
	int	pixel;
	int	x;

	ft_round_data(&pcofwall, &y);
	if (face == 1)
	{
		x = data->north.width * ((float)pcofwall / 100);
		y = data->north.height * ((float)y / 100);
		pixel = ((int)y * data->north.img.size) + (x * 4);
		data->mlx.r = data->north.img.data[pixel + 2];
		data->mlx.g = data->north.img.data[pixel + 1];
		data->mlx.b = data->north.img.data[pixel + 0];
	}
	if (face == 2)
	{
		x = data->east.width * ((float)pcofwall / 100);
		y = data->east.height * ((float)y / 100);
		pixel = ((int)y * data->east.img.size) + (x * 4);
		data->mlx.r = data->east.img.data[pixel + 2];
		data->mlx.g = data->east.img.data[pixel + 1];
		data->mlx.b = data->east.img.data[pixel + 0];
	}
	ft_pixel_of_img_2(data, face, pcofwall, y);
	data->y++;
	return ((data->mlx.r * 65536) + (data->mlx.g * 256) + data->mlx.b);
}
