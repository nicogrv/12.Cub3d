/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/30 11:24:37 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

int	ft_mouse_move(t_data *data)
{
	int		x;
	int		y;

	mlx_mouse_move(data->mlx.mlx, data->mlx.mlx_win, data->mlx.winx / 2, \
		data->mlx.winy / 2);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.mlx_win, &x, &y);
	if (x != data->mlx.winx / 2)
	{
		data->playerr -= (data->mlx.winx / 2 - x) / 2;
		if (data->playerr < 0)
			data->playerr += 360;
		else if (360 < data->playerr)
			data->playerr -= 360;
		ft_ray(data);
	}
	return (0);
}

int	ft_cross_close(t_data *data)
{
	ft_free_map(data, -42);
	ft_free_mlx(data);
	exit(0);
	return (1);
}
