/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/08 20:35:55 by nicolasgriv      ###   ########.fr       */
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
	data->anglec = 1;
	data->angles = 1;
	float angle = data->playerfov * (floor(0.5 * data->mlx.winx) - data->i) / (data->mlx.winx - 1);
	// float angle_correction = 
	printf("%.2f %.2f %.2f\n", data->playerr - data->ax, angle, 0.5 * tan((data->playerfov * (floor(0.5 * data->mlx.winx) - data->i) / (data->mlx.winx - 1))/RAD) / tan((0.5 * data->mlx.winx)/RAD));
	// printf("x = %f y = %f|x = %f y = %f", data->pleayerx, data->playery, data->posx, data->posy);
	{
		// printf("data->playerr = %.2f data->ax = %.2f\n", data->playerr,data->ax);
		// if (0 <= data->ax && data->ax < 45)
		// data->length = data->length * (data->anglec);
		// else
		{
			angle = cos((data->playerr - data->ax) / RAD);
			data->length = data->length * (angle);

		}
	data->lengthback = data->length;
	// data->length -= (0.5 * tan((data->playerfov * (floor(0.3 * data->mlx.winx) - data->i) / (data->mlx.winx - 1))/RAD) / tan((0.5 * data->mlx.winx)/RAD));
	// printf("%f\n", data->length);
		
	}
}

int	ft_ray(t_data *data)
{
	data->i = 0;
	while (data->i < (float)data->mlx.winx)
	{
		ft_ray_pt2(data);
		// printf("ax = %f\tleght = %f\n", data->ax, data->length);
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
		printf("\t %f\n", round(data->mlx.winx * (0.5 +(0.5 * tan((data->playerfov * (floor(0.5 * data->mlx.winx) - data->i) / (data->mlx.winx - 1))/RAD) / tan((0.5 * data->mlx.winx)/RAD)))));
		if (data->switchcast == 1)
		{
			ft_color_colone(data, round(data->mlx.winx * (0.5 +(0.5 * tan((data->playerfov * (floor(0.5 * data->mlx.winx) - data->i) / (data->mlx.winx - 1))/RAD) / tan((0.5 * data->mlx.winx)/RAD)))), data->length, data->pcofwall);
			// ft_draw(data, data->i, data->length*30, 0xff00ff);
			ft_draw(data, data->i, (0.5 * tan((data->playerfov * (floor(0.5 * data->mlx.winx) - data->i) / (data->mlx.winx - 1))/RAD) / tan((0.5 * data->mlx.winx)/RAD))*30, 0);		
		}
		else
		{
			ft_color_colone(data, data->i, data->lengthback, data->pcofwall);
			// ft_draw(data, data->i, data->lengthback*60, 0x0000ff);
		}
		// ft_draw(data, data->i, data->anglec*30, 0xff0000);
		
		// ft_draw(data, data->i, (-4/450*data->lengthback+1)*60, 0xff00ff);
		data->i++;
	}
	ft_ray_pt4(data);
	return (0);
}
