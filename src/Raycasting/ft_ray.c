/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/12 19:51:55 by nicolasgriv      ###   ########.fr       */
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
	if (data->ax == 90)
		data->ax = 89.9;
	if (360 <= data->ax)
		data->ax -= 360;
	else if (data->ax < 0)
		data->ax += 360;
	if (360 <= data->ax)
		data->ax -= 360;
}

int	ft_ray_pt3(t_data *data)
{
	data->posx += data->decalx;
	data->posy += data->decaly;
	if (0.97 <= data->posx - (int)data->posx)
		ft_draw_mini(data, ((int)(data->posx+1)) * data->minimap_size, (int)((data->posy) * data->minimap_size), MINI_MAP_COLOR_VOID);
	else
	{
		if (0.97 <= data->posy - (int)data->posy)
			ft_draw_mini(data, (int)((data->posx) * data->minimap_size), ((int)(data->posy+1)) * data->minimap_size, MINI_MAP_COLOR_VOID);
		else
			ft_draw_mini(data, (int)((data->posx) * data->minimap_size), (int)((data->posy) * data->minimap_size), MINI_MAP_COLOR_VOID);
	}
	if (data->map[((int)floor(data->posy))][((int)floor(data->posx))] == 1)
	{
		ft_draw_mini(data, (int)((data->posx) * data->minimap_size), (int)((data->posy) * data->minimap_size), \
			MINI_MAP_COLOR_WALL);
		return (1);
	}
	return (0);
}

void	ft_ray_pt4(t_data *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->mlx.i, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->mini.i, 0, 0);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)(data->playerx * data->minimap_size), (int)(data->playery * data->minimap_size), \
			MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)(data->playerx * data->minimap_size) - 1, (int)(data->playery * data->minimap_size), \
			MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)(data->playerx * data->minimap_size) + 1, (int)(data->playery * data->minimap_size), \
			MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)(data->playerx * data->minimap_size), (int)(data->playery * data->minimap_size) - 1, \
			MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)(data->playerx * data->minimap_size), (int)(data->playery * data->minimap_size) + 1, \
			MINI_MAP_COLOR_PLAYER);
}

void ft_fish_eye(t_data *data)
{
	float pos;

	data->length = data->length * cos((data->playerr - data->ax) / RAD);
	pos = 0.5 * tan((data->playerr - data->ax)/RAD) / tan((0.5 * data->playerfov)/RAD);
	data->nbr_column = round(data->mlx.winx * (0.5 - pos));
	
}

int	ft_ray(t_data *data)
{
	data->i = 0;
	while (data->i < (float)data->mlx.winx)
	{
		ft_ray_pt2(data);
		while (1)
		{
			if (0 <= data->ax && data->ax < 90)
				ft_ray_0_90(data); 
			else if (90 <= data->ax && data->ax < 180)
				ft_ray_90_180(data);
			else if (180 <= data->ax && data->ax < 270)
				ft_ray_180_270(data);
			else if (270 <= data->ax && data->ax < 360)
				ft_ray_270_360(data);
			if (ft_ray_pt3(data))
				break ;
		}
		ft_fish_eye(data);
		ft_color_colone(data, data->nbr_column-1, data->length, data->pcofwall);	
		ft_color_colone(data, data->nbr_column, data->length, data->pcofwall);
		data->i++;
	}
	ft_ray_pt4(data);
	return (0);
}



