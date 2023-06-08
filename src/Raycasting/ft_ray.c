/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/08 18:29:09 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

void	ft_ray_pt2(t_data *data)
{
	data->posx = data->playerx;
	data->posy = data->playery;
	data->length = 0;
	data->ax = data->playerfov / (float)data->mlx.winx * data->i + \
			data->playerr - 45;
	if (360 <= data->ax)
		data->ax -= 360;
	else if (data->ax < 0)
		data->ax += 360;
}

int	ft_ray_pt3(t_data *data)
{
	data->posx += data->decalx;
	data->posy += data->decaly;
	ft_draw_mini(data, (int)((data->posx) * 5), (int)((data->posy) * 5), \
		MINI_MAP_COLOR_WALL);
	if (data->map[((int)floor(data->posy))][((int)floor(data->posx))] == 1)
	{
		ft_draw_mini(data, (int)((data->posx) * 5), (int)((data->posy) * 5), \
			MINI_MAP_COLOR_VOID);
		return (1);
	}
	return (0);
}

void	ft_ray_pt4(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->mlx.i, 0, 0);
	// mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->mini.i, 5, 5);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5), MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5) - 1, (int)((data->playery +1) * 5), MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5) + 1, (int)((data->playery +1) * 5), MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5) - 1, MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5) + 1, MINI_MAP_COLOR_PLAYER);
}



void ft_cube_2d(int mapx, int mapy, t_data *data, int id, int size)
{
	int x = mapx*size;
	int y = mapy*size;

	while (y < mapy*size+size)
	{
		while (x < mapx*size+size)
		{
			// printf("\t\tx = %d\t y %d\n", x, y);
			if (id == -1)
				ft_draw(data, x, y, 0);
			if (id == 0)
				ft_draw(data, x, y, 0x009900);
			if (id == 1)
				ft_draw(data, x, y, 0x990000);
			x++;
		}
		x = mapx*size;
		y++;
	}
}

void ft_draw_map(t_data *data)
{
	int size = 80;
	int x = 0;
	int y = 0;
	while (y < data->mapy)
	{
		while (x < data->mapx)
		{
			if (data->map[y][x] == 0)
				ft_cube_2d(x, y, data, 0, size);
			else if (data->map[y][x] == 1)
				ft_cube_2d(x, y, data, 1, size);
			else
				ft_cube_2d(x, y, data, -1, size);
			x++;
		}
		x = 0;
		y++;
	}
	x = 0;
	y = 0;
	while(y < data->mlx.winy)
	{
		while (x < data->mlx.winx)
		{
			if (x % size == 0)
				ft_draw(data, x, y, 0);
			if (y % size == 0)
				ft_draw(data, x, y, 0);
			x++;
		}
		x = 0;
		y++;
	}
	ft_draw(data, (data->playerx ) * size, (data->playery ) * size, MINI_MAP_COLOR_PLAYER);
	ft_draw(data, (data->playerx ) * size - 1, (data->playery ) * size, MINI_MAP_COLOR_PLAYER);
	ft_draw(data, (data->playerx ) * size + 1, (data->playery ) * size, MINI_MAP_COLOR_PLAYER);
	ft_draw(data, (data->playerx ) * size, (data->playery ) * size - 1, MINI_MAP_COLOR_PLAYER);
	ft_draw(data, (data->playerx ) * size, (data->playery ) * size + 1, MINI_MAP_COLOR_PLAYER);
	int i = 0;
	// data->playerfov = 0;
	data->playerfov = 90;
	float posx = (data->playerx );
	float posy = (data->playery );
	float angle = data->playerr - data->playerfov/2;
	float iangle = (float)data->playerfov / (float)data->mlx.winx;
	// float hyv;
	// float hyh;
	while (i < data->mlx.winx * 1 + 1)
	{
		data->anglec = cos(angle/RAD); 
		data->angles = -sin(angle/RAD);
		posx = (data->playerx);
		posy = (data->playery);
		while (1)
		{
			ft_draw(data, posx, posy, 0x0000ff);
			if (data->map[(int)(posy)][(int)(posx)] == 1)
				break ;
			posx += 0.0001 * data->anglec;
			posy += 0.0001 * data->angles;
			// printf("x = %f\ty = %f\n", x, y);
		}
		printf("(%.2f)(%.2f)posx = %f\tposy = %f\n(%f)", data->playerx, data->playery, posx, posy, sqrt(pow(fabs(data->playerx - posx), 2) + pow(fabs(data->playery - posy), 2)));
		data->face = 1;
		// data->lenwall = 2;
		i++;
		angle += iangle;
		ft_color_colone(data, i, sqrt(pow(fabs(data->playerx - posx), 2) + pow(fabs(data->playery - posy), 2)), 46);
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->mlx.i, 0, 0);
}

int	ft_ray(t_data *data)
{
	data->i = 0;
	data->anglec = cos(data->playerr/RAD);
	data->angles = -sin(data->playerr/RAD);
	printf("x = %.3f y = %.3f p = %.0f c = %.2f s = %.2f\n", data->playerx, data->playery, data->playerr, data->anglec, data->angles);
	ft_draw_map(data);
	return (0);
	ft_ray_pt4(data);
	return (0);
}
