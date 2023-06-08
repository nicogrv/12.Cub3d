/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/08 16:26:51 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/cub3d.h"

int	main(int c, char **av)
{
	t_data	data;

	if (ft_init(c, av, &data))
		return (1);
	ft_initmlx(&data);
	free(data.north.path);
	free(data.south.path);
	free(data.west.path);
	free(data.east.path);
	ft_init_minimap(&data);
	data.playerr = 45;
	// data.playery = 8;
	// data.playerx = 27.1;
	data.switchcast = 1;
	// data.playerr = 90;
	// data.playery = 6.4;
	// data.playerx = 24.6;
	data.anglec = cos(data.playerr/RAD);
	data.angles = sin(data.playerr/RAD);
	ft_ray(&data);
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, &ft_key, &data);
	mlx_hook(data.mlx.mlx_win, 17, 1L << 0, &ft_cross_close, &data);
	mlx_do_key_autorepeaton(data.mlx.mlx);
	// mlx_mouse_hide(data.mlx.mlx, data.mlx.mlx_win);
	// mlx_loop_hook(data.mlx.mlx, ft_mouse_move, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
