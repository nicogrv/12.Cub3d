/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/17 16:46:52 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/cub3d.h"

int	is_ws(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
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

int	is_player(int c)
{
	if (c == 2 || c == 3 || c == 4 || c == 5)
		return (1);
	return (0);
}

int	ft_is_wc_or_new_line(char *line)
{
	int	i;

	i = 0;
	while (is_ws(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

void ft_init_id_verif_color_pt4(char *tmp, t_color *color)
{
		if (color->id == 0)
		{
			color->id++;
			color->r = ft_atoiplus(tmp);
		}
		else if (color->id == 1)
		{
			color->id++;
			color->g = ft_atoiplus(tmp);
		}
		else if (color->id == 2)
		{
			color->id++;
			color->b = ft_atoiplus(tmp);
		}
}


int ft_init_id_verif_color_pt3(char *tmp, int *j, char *line, t_color *color)
{
	while (1)
	{
		tmp = ft_substr(line, *j, ft_strlen_mode(line + *j, 2));
		if (!tmp)
			return (free(tmp), printf("SORT 1\n"), 1);
		if (color->id == 0 || color->id == 1 || color->id == 2)
			ft_init_id_verif_color_pt4(tmp, color);
		else
		{
			if (color->r == -1 || color->g == -1 || color->b == -1)
				return (free(tmp), printf(RED"Error input color3"NC), 1);
			return (free(tmp), 0);
		}
		free(tmp);
		*j += ft_strlen_mode(line + *j, 2) + 1;
	}
}


int ft_init_id_verif_color_pt2(int i, int *id, char *line, int *j)
{
	i = i + 1;
	*id = *id + 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || ft_isdigit(line[i]) == 0)
		return (printf(RED"Error input color1 %c\n"NC, line[i]));
	*j = i;
	while (ft_isdigit(line[i]) || line[i] == ',' || is_ws(line[i]))
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (printf(RED"Error input color2n"NC));
	return (0);
}
int	ft_init_id_verif_color(t_color *color, int *id, char *line, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	if (ft_init_id_verif_color_pt2(i, id, line, &j))
		return (1);
	color->id = 0;
	color->r = -1;
	color->g = -1;
	color->b = -1;
	tmp = NULL;
	if (ft_init_id_verif_color_pt3(tmp, &j, line , color))
		return (1);
	color->color = (color->r * 65536) + (color->g * 256) + color->b;
	while (is_ws(line[j]))
		j++;
	if (line[j] == '\n' || line[j] == '\0')
		return (0);
	return (1);
}

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
	if (fd == -1 || ft_is_wc_or_new_line(line + i + ft_strlen_mode(line + i, 3)) == 0)
		return (close(fd), printf(RED"Error input path2\n"NC));
	close(fd);
	return (0);
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
int ft_init_id_pt5(t_data *data, int id)
{
	if (!data->east.path || !data->west.path || !data->south.path || !data->north.path || id != 6)
		return (ft_free_path_tex(data), 1);
	else
		return (0);
}

int ft_init_id_pt4(t_data *data, char *li, int *id, int i)
{
	if (li && *id == 2 && li[i] && li[i +1] && is_ws(li[i +2]) \
			&& li[i] == 'W' && li[i +1] == 'E')
	{
		if (ft_init_id_verif_path(&data->west.path, id, li, i))
			return (ft_free_path_tex(data), 1);
	}
	else if (li && *id == 3 && li[i] && li[i +1] && is_ws(li[i +2]) \
			&& li[i] == 'E' && li[i +1] == 'A')
	{
		if (ft_init_id_verif_path(&data->east.path, id, li, i))
			return (ft_free_path_tex(data), 1);
	}
	else if (li && *id == 4 && li[i] && is_ws(li[i +1]) && li[i] == 'F')
	{
		if (ft_init_id_verif_color(&data->floor, id, li, i))
			return (ft_free_path_tex(data), 1);
	}
	else if (li && *id == 5 && li[i] && is_ws(li[i +1]) && li[i] == 'C')
	{
		if (ft_init_id_verif_color(&data->sky, id, li, i))
			return (ft_free_path_tex(data), 1);
	}
	return (0);
}

int ft_init_id_pt3(t_data *data, char *li, int *id, int i)
{
	if (li && *id == 0 && li[i] && li[i +1] && is_ws(li[i +2]) \
			&& li[i] == 'N' && li[i +1] == 'O')
	{
		if (ft_init_id_verif_path(&data->north.path, id, li, i))
			return (ft_free_path_tex(data), 1);
	}
	else if (li && *id == 1 && li[i] && li[i +1] && is_ws(li[i +2]) \
			&& li[i] == 'S' && li[i +1] == 'O')
	{
		if (ft_init_id_verif_path(&data->south.path, id, li, i))
			return (ft_free_path_tex(data), 1);
	}
	return (ft_init_id_pt4(data, li, id, i));
}

int	ft_init_id_pt2(char *li, int i, int id)
{
	if (li && id == 0 && li[i] && li[i +1] && is_ws(li[i +2]) \
				&& li[i] == 'N' && li[i +1] == 'O')
		return (1);
	else if (li && id == 1 && li[i] && li[i +1] && is_ws(li[i +2]) \
			&& li[i] == 'S' && li[i +1] == 'O')
		return (1);
	else if (li && id == 2 && li[i] && li[i +1] && is_ws(li[i +2]) \
			&& li[i] == 'W' && li[i +1] == 'E')
		return (1);
	else if (li && id == 3 && li[i] && li[i +1] && is_ws(li[i +2]) \
			&& li[i] == 'E' && li[i +1] == 'A')
		return (1);
	else if (li && id == 4 && li[i] && is_ws(li[i +1]) && li[i] == 'F')
		return (1);
	else if (li && id == 5 && li[i] && is_ws(li[i +1]) && li[i] == 'C')
		return (1);
	else
		return (0);

}

void ft_init_id_pt6(t_data *data, char **li, char **returnline)
{
	*li = get_next_line(data->fdfile);
	data->ystartmap++;
	*returnline = *li;
}

int	ft_init_id(t_data *data, char **returnline)
{
	char	*li;
	int		id;
	int		i;

	id = 0;
	li = NULL;
	ft_init_id_pt6(data, &li, returnline);
	while (li)
	{
		i = 0;
		while (li[i] && (li[i] == ' ' || li[i] == '\t'))
			i++;
		if (li[i] == '\n')
			(void) i;
		else if (ft_init_id_pt2(li, i, id))
		{
			if (ft_init_id_pt3(data, li, &id, i))
				return (1);
		}
		else
			return (ft_init_id_pt5(data, id));
		free(li);
		ft_init_id_pt6(data, &li, returnline);
	}
	return (free(li), 0);
}

void	ft_size_map(t_data *data, char *line)
{
	int		start;
	int		end;
	int		y;

	y = 0;
	start = -1;
	end = 0;
	while (line)
	{
		if (ft_is_wc_or_new_line(line) == 0)
		{
			if (start == -1)
				start = y;
			if (data->mapx < ft_strlen_mode(line, 1))
				data->mapx = ft_strlen_mode(line, 1);
			end = 0;
		}
		else
			end++;
		free(line);
		line = get_next_line(data->fdfile);
		y++;
	}
	free(line);
	data->mapy = y - end - start;
}

void	ft_map_pt3(t_data *data, int y, int x, char *line)
{
	if (line[x] == ' ')
		data->map[y][x] = 7;
	else if (line[x] == '0')
		data->map[y][x] = 0;
	else if (line[x] == '1')
		data->map[y][x] = 1;
	else if (line[x] == 'N')
		data->map[y][x] = 2;
	else if (line[x] == 'E')
		data->map[y][x] = 3;
	else if (line[x] == 'S')
		data->map[y][x] = 4;
	else if (line[x] == 'O')
		data->map[y][x] = 5;
}


int	ft_map_pt2(t_data *data, int *y, int x, int fd)
{
	char *line;

	data->map[*y] = malloc(sizeof(int) * data->mapx);
	x = -1;
	while (++x < data->mapx)
		data->map[*y][x] = 7;
	x = 0;
	line = get_next_line(fd);
	if (!line)
		return (ft_free_map(data, *y +1), 1);
	while (line[x])
	{
		if (line[x] == ' ' || line[x] == '0' || line[x] == '1' || line[x] == 'N' || line[x] == 'E' || line[x] == 'S' || line[x] == 'O')
			ft_map_pt3(data, *y, x, line);
		else if (line[x] == '\n')
			break ;
		else
			return (free(line), printf(RED"Error in map\n"NC));
		x++;
	}
	free(line);
	*y = *y + 1;
	return (0);
}


int	ft_map(t_data *data)
{
	int		fd;
	int		x;
	int		y;

	data->map = malloc(sizeof(int *) * data->mapy);
	if (!data->map)
		return (printf(RED"MALLOC\n"NC));
	fd = open(data->pathfile, O_RDONLY);
	x = 0;
	y = 0;
	while (++x < data->ystartmap)
		free(get_next_line(fd));
	while (y < data->mapy)
	{
		if (ft_map_pt2(data, &y, x, fd))
			return (1);
	}
	return (0);
}

void	ft_verif_ok_map_pt3(t_data *data)
{
	data->playerx = data->x + 0.5;
	data->playery = data->y + 0.5;
	if (data->map[data->y][data->x] == 2)
		data->playerr = 90;
	if (data->map[data->y][data->x] == 3)
		data->playerr = 180;
	if (data->map[data->y][data->x] == 4)
		data->playerr = 270;
	if (data->map[data->y][data->x] == 5)
		data->playerr = 0;
	printf(LIGHTPURPLE"P"NC);
	data->map[data->y][data->x] = 0;
	data->nbrpl++;
}

void	ft_verif_ok_map_pt2(t_data *data)
{
	if (data->map[data->y][data->x] == 1)
		printf(LIGHTRED"%d"NC, data->map[data->y][data->x]);
	else if (data->map[data->y][data->x] == 0)
		printf(LIGHTGREEN"%d"NC, data->map[data->y][data->x]);
	else if (data->map[data->y][data->x] == 7)
		printf(" ");
	if (is_player(data->map[data->y][data->x]))
		ft_verif_ok_map_pt3(data);
}


int	ft_verif_ok_map(t_data *data)
{
	data->x = -1;
	data->y = -1;
	data->nbrpl = 0;
	while (++data->y < data->mapy)
	{
		while (++data->x < data->mapx)
		{
			if ((data->y == 0 || data->x == 0 || data->y == data->mapy -1 || \
data->x == data->mapx -1) && (data->map[data->y][data->x] == 0 || \
is_player(data->map[data->y][data->x])))
				return (ft_free_map(data, -42), printf(RED"Incorrect Map 1\n"NC));
			if ((data->map[data->y][data->x] == 0 || is_player(data->map\
[data->y][data->x])) && (data->map[data->y -1][data->x] == 7 || data->map\
[data->y +1][data->x] == 7 || data->map[data->y][data->x -1] == 7 || \
data->map[data->y][data->x +1] == 7))
				return (ft_free_map(data, -42), printf(RED"Incorrect Map 2\n"NC));
			ft_verif_ok_map_pt2(data);
		}
		printf("\n");
		data->x = -1;
	}
	if (data->nbrpl != 1)
		return (ft_free_map(data, -42), printf(RED"Incorrect Number Player\n"NC));
	return (0);
}

int	ft_check_name_file(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[--i] != 'b')
		return (1);
	if (str[--i] != 'u')
		return (1);
	if (str[--i] != 'c')
		return (1);
	if (str[--i] != '.')
		return (1);
	return (0);
}
void	ft_init_2(t_data *data)
{
	printf("x%d\ty%d\n"NC, data->mapx, data->mapy);
	printf("\nN = %s\nS = %s\nO = %s\nE = %s\n"NC, data->north.path, data->south.path, data->west.path, data->east.path);
	printf("\nFloor = "LIGHTRED"%d "LIGHTGREEN"%d "LIGHTBLUE"%d"NC, data->floor.r, data->floor.g, data->floor.b);
	printf("\nSky   = "LIGHTRED"%d "LIGHTGREEN"%d "LIGHTBLUE"%d"NC, data->sky.r, data->sky.g, data->sky.b);
	printf("\nPlayer pos\tx = %.2f y %.2f\n"NC, data->playerx, data->playery);
	data->mlx.winx = WINX;
	data->mlx.winy = WINY;
	data->playerfov = FOV;
	data->lenwall = (WINY / 100) * 2;
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

void	ft_color(int nbr, t_data *data)
{
	int	tmp;

	tmp = nbr / 1048576;
	nbr = nbr - 1048576 * tmp;
	data->mlx.r = tmp * 16;
	tmp = nbr / 65536;
	nbr = nbr - 65536 * tmp;
	data->mlx.r += tmp;
	tmp = nbr / 4096;
	nbr = nbr - 4096 * tmp;
	data->mlx.g = tmp * 16;
	tmp = nbr / 256;
	nbr = nbr - 256 * tmp;
	data->mlx.g += tmp;
	tmp = nbr / 16;
	nbr = nbr - 16 * tmp;
	data->mlx.b = tmp * 16;
	data->mlx.b += nbr;
}

void	ft_draw(t_data *data, float x, float y, int color)
{
	unsigned long	pixel;

	x = roundf(x);
	y = roundf(y);
	ft_color(color, data);
	pixel = (y * data->mlx.size) + (x * 4);
	if (((unsigned long)(data->mlx.size) * data->mlx.winy) < pixel - 5 || x <= 0
		|| y <= 0 || y > data->mlx.winy || x > data->mlx.winx)
		return ;
	if (data->mlx.e == 1)
	{
		data->mlx.data[pixel + 0] = 0;
		data->mlx.data[pixel + 1] = data->mlx.r;
		data->mlx.data[pixel + 2] = data->mlx.g;
		data->mlx.data[pixel + 3] = data->mlx.b;
	}
	else if (data->mlx.e == 0)
	{
		data->mlx.data[pixel + 0] = data->mlx.b;
		data->mlx.data[pixel + 1] = data->mlx.g;
		data->mlx.data[pixel + 2] = data->mlx.r;
		data->mlx.data[pixel + 3] = 0;
	}
}

void	ft_draw_mini(t_data *data, float x, float y, int color)
{
	unsigned long	pixel;

	x = roundf(x);
	y = roundf(y);
	ft_color(color, data);
	pixel = (y * data->mini.img.size) + (x * 4);
	if (data->mini.img.e == 1)
	{
		data->mini.img.data[pixel + 0] = 1;
		data->mini.img.data[pixel + 1] = data->mlx.r;
		data->mini.img.data[pixel + 2] = data->mlx.g;
		data->mini.img.data[pixel + 3] = data->mlx.b;
	}
	else if (data->mini.img.e == 0)
	{
		data->mini.img.data[pixel + 0] = data->mlx.b;
		data->mini.img.data[pixel + 1] = data->mlx.g;
		data->mini.img.data[pixel + 2] = data->mlx.r;
		data->mini.img.data[pixel + 3] = 1;
	}
}

void	ft_pixel_of_img_2(t_data *data, int face, int pcofwall, int y)
{
	int	pixel;
	int	x;

	if (face == 3)
	{
		x = data->south.width * ((float)pcofwall / 100);
		y = data->south.height * ((float)y / 100);
		pixel = (y * data->south.img.size) + (x * 4);
		data->mlx.r = data->south.img.data[pixel + 2];
		data->mlx.g = data->south.img.data[pixel + 1];
		data->mlx.b = data->south.img.data[pixel + 0];
	}
	if (face == 4)
	{
		x = data->west.width * ((float)pcofwall / 100);
		y = data->west.height * ((float)y / 100);
		pixel = (y * data->west.img.size) + (x * 4);
		data->mlx.r = data->west.img.data[pixel + 2];
		data->mlx.g = data->west.img.data[pixel + 1];
		data->mlx.b = data->west.img.data[pixel + 0];
	}
}

int	ft_pixel_of_img(t_data *data, int face, int pcofwall, int y)
{
	int	pixel;
	int	x;

	if (face == 1)
	{
		x = data->north.width * ((float)pcofwall / 100);
		y = data->north.height * ((float)y / 100);
		pixel = (y * data->north.img.size) + (x * 4);
		data->mlx.r = data->north.img.data[pixel + 2];
		data->mlx.g = data->north.img.data[pixel + 1];
		data->mlx.b = data->north.img.data[pixel + 0];
	}
	if (face == 2)
	{
		x = data->east.width * ((float)pcofwall / 100);
		y = data->east.height * ((float)y / 100);
		pixel = (y * data->east.img.size) + (x * 4);
		data->mlx.r = data->east.img.data[pixel + 2];
		data->mlx.g = data->east.img.data[pixel + 1];
		data->mlx.b = data->east.img.data[pixel + 0];
	}
	ft_pixel_of_img_2(data, face, pcofwall, y);
	return ((data->mlx.r * 65536) + (data->mlx.g * 256) + data->mlx.b);
}

void	ft_color_colone(t_data *data, int x, float len, int pcofwall, int face)
{
	int				y;
	int				wall;
	int				start;
	static int		saveface;
	static float	savelen = {0};

	y = 0;
	if (pcofwall == 100)
		pcofwall = 99;
	if ((5 < pcofwall && pcofwall < 95) || (fabs(savelen - len) > 0.1))
		saveface = face;
	if ((fabs(savelen - len) < 0.4) && ((pcofwall <= 1 && (face == 4 || face == 2)) || (pcofwall >= 98 && (face == 1 || face == 3))))
		face = saveface;
	wall = (data->mlx.winy / 2) + (10 / len) * data->lenwall - ((data->mlx.winy / 2) - (10 / len) * data->lenwall);
	if (data->mlx.winy < wall)
		y = data->mlx.winy - wall;
	while (y < (data->mlx.winy / 2) - (10 / len) * data->lenwall)
	{
		ft_draw(data, x, y, data->sky.color);
		y++;
	}
	start = y;
	while (y < (data->mlx.winy / 2) + (10 / len) * data->lenwall)
	{
		// printf("coucou = %d\n",;
		// ft_draw(data, x, y, 0xFF0000);
		ft_draw(data, x, y, ft_pixel_of_img(data, face, pcofwall, ((y - start) * 100 / wall)));
		y++;
	}
	while (y < data->mlx.winy)
	{
		ft_draw(data, x, y, data->floor.color);
		y++;
	}
	savelen = len;
}
int	ft_ray(t_data *data);

int	ft_mouse_move(t_data *data)
{
	int		x;
	double	i;
	int		y;

	mlx_mouse_move(data->mlx.mlx, data->mlx.mlx_win, data->mlx.winx / 2, data->mlx.winy / 2);
	mlx_mouse_get_pos(data->mlx.mlx, data->mlx.mlx_win, &x, &y);
	if (x != data->mlx.winx / 2)
	{
		data->playerr -= (data->mlx.winx / 2 - x) / 2;
		// printf("dif = %d\n",  (data->mlx.winx / 2) - x);
			if (data->playerr < 0)
			data->playerr += 360;
			else if (360 < data->playerr)
			data->playerr -= 360;
		i = 0;
		// while (i < 100000000)
			// i++;
		ft_ray(data);
	}
	return (0);
}

int	ft_ray(t_data *data)
{
	float	i;
	float	ax;
	float	hyv;
	float	hyr;
	float	posx;
	float	posy;
	float	decalx;
	float	decaly;
	float	length;
	int		face;
	int		pcofwall;

	i = 0;
	while (i < (float)data->mlx.winx)
	{
		posx = data->playerx;
		posy = data->playery;
		length = 0.1;
		ax = data->playerfov / (float)data->mlx.winx * i + data->playerr - 45;
		if (ax == 90)
			ax = 89.9;
		if (360 <= ax)
			ax -= 360;
		else if (ax < 0)
			ax += 360;
		// printf("\n\n\n\t\t----NEW RAY----\n\n\n");
		while (1)
		{
			// printf("Start pos Ray x = %.2f y = %.2f len = %.2f\n",posx, posy, length);
			if (0 <= ax && ax < 90)
			{
				if (ax == 0)
					ax = 0.1;
				if (ax == 90)
					ax = 89.9;
				hyv = (posy - (int)posy) / cos((90 - ax) / RAD);
				hyr = (posx - (int)posx) / cos(ax / RAD);
				if (hyv < -5)
					hyv = 5;
				if (hyv < hyr)
				{
					decaly = ((posy - (int)posy) * -1) - 0.001;
					decalx = ((posy - (int)posy) * -1) * tan((90 - ax) / RAD) - 0.001 ;
					length += hyv;
					face = 1;
					pcofwall = (int)((posx + decalx - (int)(posx + decalx)) * 100);
				}
				else
				{
					decaly = ((posx - (int)posx) * -1) * tan((ax) / RAD) - 0.001 ;
					decalx = ((posx - (int)posx) * -1) - 0.001;
					length += hyr;
					face = 4;
					pcofwall = 100 - ((int)((posy + decaly - (int)(posy + decaly)) * 100));
				}
			}
			else if (90 <= ax && ax < 180)
			{
				ax -= 90;
				if (ax == 0)
					ax = 0.1;
				hyv = (posy - (int)posy) / cos(ax / RAD);
				hyr = (1 - (posx - (int)posx)) / cos((90 - ax) / RAD);
				if (hyv < hyr)
				{
					decaly = ((posy - (int)posy) * -1) - 0.001;
					decalx = (posy - (int)posy) * tan((ax) / RAD) - 0.001 ;
					length += hyv;
					face = 1;
					pcofwall = (int)((posx + decalx - (int)(posx + decalx)) * 100);
				}
				else
				{
					decaly = ((1 - (posx - (int)posx)) * -1) * tan((90 - ax) / RAD) + 0.001;
					decalx = (1 - (posx - (int)posx)) + 0.001;
					length += hyr;
					face = 2;
					pcofwall = (int)((posy + decaly - (int)(posy + decaly)) * 100);
				}
				ax += 90;
			}
			else if (180 <= ax && ax < 270)
			{
				ax -= 180;
				if (ax == 0)
					ax = 0.1;
				hyv = (1 - (posy - (int)posy)) / cos((90 - ax) / RAD);
				hyr = (1 - (posx - (int)posx)) / cos(ax / RAD);
				if (hyv < hyr)
				{
					decaly = (1 - (posy - (int)posy)) + 0.001;
					decalx = (1 - (posy - (int)posy)) * tan((90 - ax) / RAD) + 0.001 ;
					length += hyv;
					face = 3;
					pcofwall = 100 - ((int)((posx + decalx - (int)(posx + decalx)) * 100));
				}
				else
				{
					decaly = (1 - (posx - (int)posx)) * tan((ax) / RAD) + 0.001 ;
					decalx = (1 - (posx - (int)posx)) + 0.001;
					length += hyr ;
					face = 2;
					pcofwall = (int)((posy + decaly - (int)(posy + decaly)) * 100);
				}
				ax += 180;
			}
			else if ((270 <= ax && ax < 360))
			{
				ax -= 270;
				if (ax == 0)
					ax = 0.1;
				hyv = (1 - (posy - (int)posy)) / cos(ax / RAD);
				hyr = ((posx - (int)posx)) / cos((90 - ax) / RAD);
				if (hyv < hyr)
				{
					decaly = (1 - (posy - (int)posy)) + 0.001;
					decalx = ((1 - (posy - (int)posy)) * -1) * tan((ax) / RAD) + 0.001 ;
					length += hyv;
					face = 3;
					pcofwall = 100 - ((int)((posx + decalx - (int)(posx + decalx)) * 100));
				}
				else
				{
					decaly = (posx - (int)posx) * tan((90 - ax) / RAD) - 0.001;
					decalx = ((posx - (int)posx) * -1) - 0.001;
					length += hyr;
					face = 4;
					pcofwall = 100 - ((int)((posy + decaly - (int)(posy + decaly)) * 100));
				}
				ax += 270;
			}
			// if (hyr < hyv)
				// printf(LIGHTRED" %.3f"LIGHTGREEN" %.3f\t%.2f\n"NC, hyr, hyv, ax);
			// else
				// printf(LIGHTGREEN" %.3f "LIGHTRED"%.3f\t%.2f\n"NC, hyv, hyr, ax);
			// printf("Decalx = %.3f Decaly = %.3f\n", decalx, decaly);
			posx += decalx;
			posy += decaly;
			ft_draw_mini(data, (int)((posx) * 5), (int)((posy) * 5), MINI_MAP_COLOR_WALL);
			// fprintf(stderr, NC"y = %d(%.2f) x = %d(%.2f) pcdecal = %d\n", (int)floor(posy), posy,  (int)floor(posx), posx, pcofwall);
			if (data->map[((int)floor(posy))][((int)floor(posx))] == 1)
			{
				ft_draw_mini(data, (int)((posx) * 5), (int)((posy) * 5), MINI_MAP_COLOR_VOID);
				// printf("BREAK x = %d(%f) y = %d(%f) len = %.2f\n\n", (int)floor(posx), posx, (int)floor(posy), posy, length);
				break ;
			}
		}
		// printf("length = %.5f\n\n\n\n", length);
		ft_color_colone(data, i, length, pcofwall, face);
		i++;
		// printf("x = %.1fy = %.1f r = %.1f f=%d angle = %.2f\n", data->playerx, data->playery, data->playerr,data->playerfov, ax);
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->mlx.i, 0, 0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->mini.i, 5, 5);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5), MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5) - 1, (int)((data->playery +1) * 5), MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5) + 1, (int)((data->playery +1) * 5), MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5) - 1, MINI_MAP_COLOR_PLAYER);
	mlx_pixel_put(data->mlx.mlx, data->mlx.mlx_win, (int)((data->playerx + 1) * 5), (int)((data->playery +1) * 5) + 1, MINI_MAP_COLOR_PLAYER);
	return (0);
}

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

int	ft_cross_close(t_data *data)
{
	ft_free_map(data, -42);
	ft_free_mlx(data);
	exit(0);
	return (1);
}

int	ft_key(int keycode, t_data *data)
{
	if (keycode == TOUCH_LEFTARROW)
			data->playerr -= 15;
	else if (keycode == TOUCH_RIGHTARROW)
			data->playerr += 15;
	else if (keycode == TOUCH_W)
	{
		if (data->map[((int)floor(data->playery + 0.42 * -sin(data->playerr / RAD)))][((int)floor(data->playerx + 0.42 * -cos(data->playerr / RAD)))] == 0)
		{
			data->playery += 0.2 * -sin(data->playerr / RAD);
			data->playerx += 0.2 * -cos(data->playerr / RAD);
		}
	}
	else if (keycode == TOUCH_S)
	{
		if (data->map[((int)floor(data->playery + 0.42 * sin(data->playerr / RAD)))][((int)floor(data->playerx + 0.42 * cos(data->playerr / RAD)))] == 0)
		{
			data->playery += 0.2 * sin(data->playerr / RAD);
			data->playerx += 0.2 * cos(data->playerr / RAD);
		}
	}
	else if (keycode == TOUCH_A)
	{
		if (data->map[((int)floor(data->playery + 0.42 * cos(data->playerr / RAD)))][((int)floor(data->playerx + 0.42 * -sin(data->playerr / RAD)))] == 0)
		{
			data->playerx += 0.2 * -sin(data->playerr / RAD);
			data->playery += 0.2 * cos(data->playerr / RAD);
		}
	}
	else if (keycode == TOUCH_D)
	{
		if (data->map[((int)floor(data->playery + 0.42 * -cos(data->playerr / RAD)))][((int)floor(data->playerx + 0.42 * sin(data->playerr / RAD)))] == 0)
		{
			data->playerx += 0.2 * sin(data->playerr / RAD);
			data->playery += 0.2 * -cos(data->playerr / RAD);
		}
	}
	else if (keycode == TOUCH_PLUS)
			data->playerfov -= 10;
	else if (keycode == TOUCH_MOINS)
			data->playerfov += 10;
	else if (keycode == TOUCH_N)
			data->lenwall -= 1;
	else if (keycode == TOUCH_M)
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
	mlx_destroy_image(data->mlx.mlx, data->mlx.i);
	data->mlx.i = mlx_new_image(data->mlx.mlx, data->mlx.winx, data->mlx.winy);
	ft_ray(data);
	return (0);
}

void	ft_init_minimap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->mapy * 5)
	{
		x = 0;
		while (x < data->mapx * 5)
		{
			ft_draw_mini(data, x, y, data->sky.color);
			x++;
		}
		y++;
	}
}

int	main(int c, char **av)
{
	t_data	data;

	if (ft_init(c, av, &data))
		return (1);
	data.mlx.mlx = mlx_init();
	data.mlx.mlx_win = mlx_new_window(data.mlx.mlx, data.mlx.winx, data.mlx.winy, "Cub3d");
	data.mlx.i = mlx_new_image(data.mlx.mlx, data.mlx.winx, data.mlx.winy);
	data.mlx.data = mlx_get_data_addr(data.mlx.i, &data.mlx.p, &data.mlx.size, &data.mlx.e);
	data.north.tex = mlx_xpm_file_to_image(data.mlx.mlx, data.north.path, &data.north.width, &data.north.height);
	data.north.img.data = mlx_get_data_addr(data.north.tex, &data.north.img.p, &data.north.img.size, &data.north.img.e);
	data.east.tex = mlx_xpm_file_to_image(data.mlx.mlx, data.east.path, &data.east.width, &data.east.height);
	data.east.img.data = mlx_get_data_addr(data.east.tex, &data.east.img.p, &data.east.img.size, &data.east.img.e);
	data.south.tex = mlx_xpm_file_to_image(data.mlx.mlx, data.south.path, &data.south.width, &data.south.height);
	data.south.img.data = mlx_get_data_addr(data.south.tex, &data.south.img.p, &data.south.img.size, &data.south.img.e);
	data.west.tex = mlx_xpm_file_to_image(data.mlx.mlx, data.west.path, &data.west.width, &data.west.height);
	data.west.img.data = mlx_get_data_addr(data.west.tex, &data.west.img.p, &data.west.img.size, &data.west.img.e);
	free(data.north.path);
	free(data.south.path);
	free(data.west.path);
	free(data.east.path);
	data.mini.i = mlx_new_image(data.mlx.mlx, data.mapx * 5, data.mapy * 5);
	data.mini.img.data = mlx_get_data_addr(data.mini.i, &data.mini.img.p, &data.mini.img.size, &data.mini.img.e);
	ft_init_minimap(&data);
	ft_ray(&data);
	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, &ft_key, &data);
	mlx_hook(data.mlx.mlx_win, 17, 1L << 0, &ft_cross_close, &data);
	mlx_do_key_autorepeaton(data.mlx.mlx);
	mlx_mouse_hide(data.mlx.mlx, data.mlx.mlx_win);
	mlx_loop_hook(data.mlx.mlx, ft_mouse_move, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
