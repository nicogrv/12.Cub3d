/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/14 15:24:27 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/cub3d.h"

// mlx_mouse_hide(data.mlx.mlx, data.mlx.mlx_win);
// Decommanter et mettre avant "mlx_loop" (leaks)

int	main(int c, char **av)
{
	t_data	data;

	if (ft_init(c, av, &data))
		return (printf(LIGHTRED"Error\n"NC), 1);
	data.mlx.mlx = mlx_init();
	ft_initmlx(&data);
	free(data.north.path);
	free(data.south.path);
	free(data.west.path);
	free(data.east.path);
	ft_init_minimap(&data);
	data.playerr = 180;
	data.playerx = 17.499985;
	data.playery = 8.500000;
	ft_ray(&data);
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, &ft_key, &data);
	mlx_hook(data.mlx.mlx_win, 17, 1L << 0, &ft_cross_close, &data);
	mlx_do_key_autorepeaton(data.mlx.mlx);
	mlx_loop_hook(data.mlx.mlx, ft_mouse_move, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
