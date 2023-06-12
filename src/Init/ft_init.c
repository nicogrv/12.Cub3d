/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/12 20:16:02 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

int	ft_init_id_verif_path(char **path_for_data, int *id, char *line, int i)
{
	int	fd;

	*id = *id + 1;
	i = i + 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (printf(RED"Error input path1\n"NC));
	*path_for_data = ft_substr(line, i, ft_strlen_mode(line + i, 3));
	fd = open(*path_for_data, O_RDONLY);
	if (fd == -1 || ft_is_wc_or_new_line(line + i + \
				ft_strlen_mode(line + i, 3)) == 0)
		return (close(fd), printf(RED"Error input path2\n"NC));
	close(fd);
	return (0);
}

void	ft_init_2(t_data *data)
{
	printf("x%d\ty%d\n"NC, data->mapx, data->mapy);
	printf("\nN = %s\nS = %s\nO = %s\nE = %s\n"NC, data->north.path, \
				data->south.path, data->west.path, data->east.path);
	printf("\nFloor = "LIGHTRED"%d "LIGHTGREEN"%d "LIGHTBLUE"%d"NC, \
				data->floor.r, data->floor.g, data->floor.b);
	printf("\nSky   = "LIGHTRED"%d "LIGHTGREEN"%d "LIGHTBLUE"%d"NC, \
				data->sky.r, data->sky.g, data->sky.b);
	printf("\nPlayer pos\tx = %.2f y %.2f\n"NC, data->playerx, \
				data->playery);
	data->mlx.winx = WINX;
	data->mlx.winy = WINY;
	data->playerfov = FOV;
	data->lenwall = (WINX / 100) * 2;
	data->minimap_size = MINI_MAP_SIZE;
}

void	ft_initmlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->mlx.winx,data->mlx.winy, "Cub3d");
	data->mlx.i = mlx_new_image(data->mlx.mlx, data->mlx.winx, data->mlx.winy);
	data->mlx.data = 		mlx_get_data_addr(data->mlx.i, &data->mlx.p, &data->mlx.size, &data->mlx.e);
	data->north.tex = 	mlx_xpm_file_to_image(data->mlx.mlx, data->north.path, &data->north.width, &data->north.height);
	data->north.img.data = 	mlx_get_data_addr(data->north.tex, &data->north.img.p, &data->north.img.size, &data->north.img.e);
	data->east.tex = 	mlx_xpm_file_to_image(data->mlx.mlx, data->east.path, &data->east.width, &data->east.height);
	data->east.img.data = 	mlx_get_data_addr(data->east.tex, &data->east.img.p, &data->east.img.size, &data->east.img.e);
	data->south.tex = 	mlx_xpm_file_to_image(data->mlx.mlx, data->south.path, &data->south.width, &data->south.height);
	data->south.img.data = 	mlx_get_data_addr(data->south.tex, &data->south.img.p, &data->south.img.size, &data->south.img.e);
	data->west.tex = 	mlx_xpm_file_to_image(data->mlx.mlx, data->west.path, &data->west.width, &data->west.height);
	data->west.img.data = 	mlx_get_data_addr(data->west.tex, &data->west.img.p, &data->west.img.size, &data->west.img.e);
	data->mini.i =				mlx_new_image(data->mlx.mlx, data->mapx * data->minimap_size, data->mapy * data->minimap_size);
	data->mini.img.data = 	mlx_get_data_addr(data->mini.i, &data->mini.img.p, &data->mini.img.size, &data->mini.img.e);
}

int	ft_init(int c, char **av, t_data *data)
{
	char	*line;

	line = NULL;
	data->north.path = NULL;
	data->south.path = NULL;
	data->west.path = NULL;
	data->east.path = NULL;
	data->mapx = 0;
	data->ystartmap = 0;
	if (c != 2 || ft_check_name_file(av[1]))
		return (printf(RED"Error number of arg1\n"NC));
	data->fdfile = open(av[1], O_RDONLY);
	if (data->fdfile == -1)
		return (printf(RED"Error path of arg2\n"NC));
	data->pathfile = av[1];
	if (ft_init_id(data, &line))
		return (free(line), printf(RED"Error in file3\n"NC));
	ft_size_map(data, line);
	close(data->fdfile);
	if (ft_map(data))
		return (ft_free_path_tex(data), 1);
	if (ft_verif_ok_map(data))
		return (ft_free_path_tex(data), 1);
	ft_init_2(data);
	return (0);
}

void	ft_init_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->mapy * data->minimap_size)
	{
		x = 0;
		while (x < data->mapx * data->minimap_size)
		{
			ft_draw_mini(data, x, y, data->sky.color);
			x++;
		}
		y++;
	}
}
