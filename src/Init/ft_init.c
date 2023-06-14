/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/14 14:21:09 by ngriveau         ###   ########.fr       */
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

void	ft_initmlx(t_data *d)
{
	d->mlx.mlx_win = mlx_new_window(d->mlx.mlx, d->mlx.winx, \
		d->mlx.winy, "Cub3d");
	d->mlx.i = mlx_new_image(d->mlx.mlx, d->mlx.winx, d->mlx.winy);
	d->mlx.data = mlx_get_data_addr(d->mlx.i, &d->mlx.p, \
							&d->mlx.size, &d->mlx.e);
	d->north.tex = mlx_xpm_file_to_image(d->mlx.mlx, d->north.path, \
		&d->north.width, &d->north.height);
	d->north.img.data = mlx_get_data_addr(d->north.tex, \
		&d->north.img.p, &d->north.img.size, &d->north.img.e);
	d->east.tex = mlx_xpm_file_to_image(d->mlx.mlx, d->east.path, \
		&d->east.width, &d->east.height);
	d->east.img.data = mlx_get_data_addr(d->east.tex, &d->east.img.p, \
		&d->east.img.size, &d->east.img.e);
	d->south.tex = mlx_xpm_file_to_image(d->mlx.mlx, d->south.path, \
		&d->south.width, &d->south.height);
	d->south.img.data = mlx_get_data_addr(d->south.tex, \
		&d->south.img.p, &d->south.img.size, &d->south.img.e);
	d->west.tex = mlx_xpm_file_to_image(d->mlx.mlx, d->west.path, \
		&d->west.width, &d->west.height);
	d->west.img.data = mlx_get_data_addr(d->west.tex, &d->west.img.p, \
		&d->west.img.size, &d->west.img.e);
	d->mini.i = mlx_new_image(d->mlx.mlx, d->mapx * \
		d->minimap_size, d->mapy * d->minimap_size);
	d->mini.img.data = mlx_get_data_addr(d->mini.i, &d->mini.img.p, \
		&d->mini.img.size, &d->mini.img.e);
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
