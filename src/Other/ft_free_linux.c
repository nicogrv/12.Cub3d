/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/30 11:24:49 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

int	ft_free_mlx(t_data *data)
{
	mlx_destroy_image(data->mlx.mlx, data->north.tex);
	mlx_destroy_image(data->mlx.mlx, data->east.tex);
	mlx_destroy_image(data->mlx.mlx, data->south.tex);
	mlx_destroy_image(data->mlx.mlx, data->west.tex);
	mlx_destroy_image(data->mlx.mlx, data->mini.i);
	mlx_destroy_image(data->mlx.mlx, data->mlx.i);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	exit(0);
	return (1);
}

void	ft_free_path_tex(t_data *data)
{
	if (data->north.path != NULL)
		free(data->north.path);
	if (data->south.path != NULL)
		free(data->south.path);
	if (data->west.path != NULL)
		free(data->west.path);
	if (data->east.path != NULL)
		free(data->east.path);
	return ;
}

void	ft_free_map(t_data *data, int y)
{
	int	i;

	i = -1;
	if (y == -42)
		y = data->mapy;
	while (++i < y)
		free(data->map[i]);
	free(data->map);
}
