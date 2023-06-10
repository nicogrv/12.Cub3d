/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/10 12:52:14 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

void	ft_key_4(int keycode, t_data *data)
{
	if (keycode == TOUCH_W)
	{
		if (data->map[((int)floor(data->playery + 0.42 * -sin(data->playerr / \
RAD)))][((int)floor(data->playerx + 0.42 * -cos(data->playerr / RAD)))] == 0)
		{
			data->playery += 0.2 * -sin(data->playerr / RAD);
			data->playerx += 0.2 * -cos(data->playerr / RAD);
		}
	}
	if (keycode == TOUCH_S)
	{
		if (data->map[((int)floor(data->playery + 0.42 * sin(data->playerr / \
RAD)))][((int)floor(data->playerx + 0.42 * cos(data->playerr / RAD)))] == 0)
		{
			data->playery += 0.2 * sin(data->playerr / RAD);
			data->playerx += 0.2 * cos(data->playerr / RAD);
		}
	}
}

void	ft_key_3(int keycode, t_data *data)
{
	if (keycode == TOUCH_A)
	{
		if (data->map[((int)floor(data->playery + 0.42 * cos(data->playerr / \
RAD)))][((int)floor(data->playerx + 0.42 * -sin(data->playerr / RAD)))] == 0)
		{
			data->playerx += 0.2 * -sin(data->playerr / RAD);
			data->playery += 0.2 * cos(data->playerr / RAD);
		}
	}
	if (keycode == TOUCH_D)
	{
		if (data->map[((int)floor(data->playery + 0.42 * -cos(data->playerr / \
RAD)))][((int)floor(data->playerx + 0.42 * sin(data->playerr / RAD)))] == 0)
		{
			data->playerx += 0.2 * sin(data->playerr / RAD);
			data->playery += 0.2 * -cos(data->playerr / RAD);
		}
	}
	ft_key_4(keycode, data);
}

void	ft_key_2(int keycode, t_data *data)
{
	if (keycode == TOUCH_PLUS)
			data->playerfov -= 10;
	if (keycode == TOUCH_MOINS)
			data->playerfov += 10;
	if (keycode == TOUCH_N)
			data->lenwall -= 1;
	if (keycode == TOUCH_M)
			data->lenwall += 1;
	if (data->playerr < 0)
		data->playerr += 360;
	if (360 < data->playerr)
		data->playerr -= 360;
	if (data->playerfov < 30)
		data->playerfov = 30;
	if (180 < data->playerfov)
		data->playerfov = 180;
	if (keycode == ESC || keycode == -16779872)
		ft_cross_close(data);
	// data->playerr = 90;
	// data->playery = 6.7;
	// data->playerx = 20.6;
	printf("x = %f, y = %f\n", data->playerx, data->playery);
	ft_key_3(keycode, data);
}

int	ft_key(int keycode, t_data *data)
{
	if (keycode == TOUCH_LEFTARROW)
			data->playerr -= 15;
	else if (keycode == TOUCH_RIGHTARROW)
			data->playerr += 15;
	ft_key_2(keycode, data);
	// mlx_destroy_image(data->mlx.mlx, data->mlx.i);
	// data->mlx.i = mlx_new_image(data->mlx.mlx, data->mlx.winx, data->mlx.winy);
	ft_ray(data);
	return (0);
}
