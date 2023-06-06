/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/06 19:21:10 by nicolasgriv      ###   ########.fr       */
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
	// mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
	// 	data->mini.i, 5, 5);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5), \
			MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)((data->playerx + 1) * 5) - 1, (int)((data->playery +1) * 5), \
			MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)((data->playerx + 1) * 5) + 1, (int)((data->playery +1) * 5), \
			MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5) - 1, \
			MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, \
		(int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5) + 1, \
			MINI_MAP_COLOR_PLAYER);
}

void ft_fish_eye(t_data *data)
{
	float angle;
	// float x;
	// float y;
	// float py;
	
	printf("%f,", data->length);
	// printf("x = %f y = %f|x = %f y = %f", data->pleayerx, data->playery, data->posx, data->posy);
	// if (89.9 < data->ax && data->ax < 90.0)
	// if (0 <= data->ax && data->ax < 90)
	{
		// printf("data->playerr = %.2f data->ax = %.2f\n", data->playerr,data->ax);
		if (data->ax <= data->playerr)
		{
			angle = cos(((data->playerr - data->ax) / RAD)); 
			data->length = data->length * (angle);

		}
		else
		{
			angle = cos((data->ax - data->playerr) / RAD);
			data->length = data->length * (angle);

		}
	printf("%f\n", data->length);
		
	}
}

int	ft_ray(t_data *data)
{
	data->i = 0;
	while (data->i < (float)data->mlx.winx)
	{
		ft_ray_pt2(data);
		printf("ax = %f\tleght = %f\n", data->ax, data->length);
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
		ft_color_colone(data, data->i, data->length, data->pcofwall);
		ft_draw(data, data->i, data->length*10, 0xff0000);
		ft_draw(data, data->i, data->length*10, 0xff0000);
		data->i++;
	}
	ft_ray_pt4(data);
	return (0);
}
