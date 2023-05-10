/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/10 12:02:51 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/cub3d.h"

int is_ws(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int is_player(int c)
{
	if (c == 2 || c == 3 || c == 4 || c == 5)
		return (1);
	return (0);
}

int ft_is_wc_or_new_line(char *line)
{
	int i;

	i = 0;
	while (is_ws(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

int	ft_init_id_verif_color(t_color *color, int *id, char *line, int i)
{
	char *tmp;
	int j;
	int colorid;

	*id = *id + 1;
	i = i + 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0' || ft_isdigit(line[i]) == 0)
		return (printf(RED"Error input color1 %c\n"NC, line[i]));
	j = i;
	while (ft_isdigit(line[i]) || line[i] == ',' || is_ws(line[i]))
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		return (printf(RED"Error input color2n"NC));
	colorid = 0;
	color->r = -1;
	color->g = -1;
	color->b = -1;
	while (1)
	{
		tmp = ft_substr(line, j, ft_strlen_mode(line + j, 2));
		if (!tmp)
			return (-1);
		if (colorid == 0)
		{
			colorid++;
			color->r = ft_atoiplus(tmp);
		}
		else if (colorid == 1)
		{
			colorid++;
			color->g = ft_atoiplus(tmp);
		}
		else if (colorid == 2)
		{
			colorid++;
			color->b = ft_atoiplus(tmp);
		}
		else
		{
			if (color->r == -1 || color->g == -1 || color->b == -1)
				return (printf(RED"Error input color3"NC));
			break;
		}
		j += ft_strlen_mode(line + j, 2) + 1;
	}
	color->color = (color->r * 65536) + (color->g * 256) + color->b;
	while (is_ws(line[j]))
		j++;
	if (line[j] == '\n' || line[j] == '\0')
		return (0);
	return (1);
	
}



int	ft_init_id_verif_path(char **path_for_data, int *id, char *line, int i)
{
	char *path;
	int		fd;

	*id = *id + 1;
	i = i + 2;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '\0')
		return (printf(RED"Error input path1\n"NC));		
	path = ft_substr(line, i, ft_strlen_mode(line+i, 3));
	fd = open(path, O_RDONLY);
	if (fd == -1 || ft_is_wc_or_new_line( line + i + ft_strlen_mode(line+i, 3)) == 0)
	{
		*path_for_data = NULL;
		return (printf(RED"Error input path2\n"NC));	
	}
	*path_for_data = path;
	return (0);
	
}


int	ft_init_id(t_data *data, char **returnline)
{
	char	*line;
	int		id;
	int		i;

	id = 0;
	line = get_next_line(data->fdfile);
	data->ystartmap++;
	*returnline = line;
	while(line)
	{
		i = 0;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (line[i] == '\n')
			(void) i;
		else if (line && id == 0 && line[i] && line[i+1] && is_ws(line[i+2]) && line[i] == 'N' && line[i+1] == 'O')
		{
			if (ft_init_id_verif_path(&data->pathnorth, &id, line, i))
				return (1);
		}
		else if (line && id == 1 && line[i] && line[i+1] && is_ws(line[i+2]) && line[i] == 'S' && line[i+1] == 'O')
		{
			if (ft_init_id_verif_path(&data->pathsouth, &id, line, i))
				return (1);
		}
		else if (line && id == 2 && line[i] && line[i+1] && is_ws(line[i+2]) && line[i] == 'W' && line[i+1] == 'E')
		{
			if (ft_init_id_verif_path(&data->pathwest, &id, line, i))
				return (1);
		}
		else if (line && id == 3 && line[i] && line[i+1] && is_ws(line[i+2]) && line[i] == 'E' && line[i+1] == 'A')
		{
			if (ft_init_id_verif_path(&data->patheast, &id, line, i))
				return (1);
		}
		else if (line && id == 4 && line[i] && is_ws(line[i+1]) && line[i] == 'F')
		{
			if (ft_init_id_verif_color(&data->floor, &id, line, i))
				return (1);
		}
		else if (line && id == 5 && line[i] && is_ws(line[i+1]) && line[i] == 'C')
		{
			if (ft_init_id_verif_color(&data->sky, &id, line, i))
				return (1);
		}
		else
		{
			if (!data->patheast || !data->pathwest || !data->pathsouth || !data->pathnorth)
				return (1);
			else
				return (0);
		}
		free(line);
		line = get_next_line(data->fdfile);
		data->ystartmap++;
		*returnline = line;
	}
	return (0);
}



void	ft_size_map(t_data *data, char *line)
{
	int		start;
	int		end;
	int		y;
	
	y = 0;
	start = -1;
	end = 0;
	data->mapx = 0;
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



int ft_map(t_data *data)
{
	int fd;
	int x;
	int y;
	char *line;
	
	data->map = malloc(sizeof(int *) * data->mapy);
	if (!data->map)
		return (printf(RED"MALLOC\n"NC));
	fd = open(data->pathfile, O_RDONLY);
	x = 0;
	y = 0;
	while(++x < data->ystartmap)
		free(get_next_line(fd));
	while (y < data->mapy)
	{
		data->map[y] = malloc(sizeof(int) * data->mapx);
		x = -1;
		while (++x < data->mapx)
			data->map[y][x] = 7;
		x = 0;
		line = get_next_line(fd);
		while (line[x])
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
			else if (line[x] == '\n')
				break ;
			else 
				return (printf(RED"Error in map\n"NC));
			x++;
		}
		y++;
		
	}
	return (0);
}

int ft_verif_ok_map(t_data *data)
{
	int x;
	int y;
	int player;

	x = -1;
	y = -1;
	player = 0;
	while (++y < data->mapy)
	{
		while (++x < data->mapx)
		{
			if ((y == 0 || x == 0 || y == data->mapy - 1 || x == data->mapx - 1) && (data->map[y][x] == 0 || is_player(data->map[y][x])) )
				return (printf(RED"Incorrect Map 1\n"NC));
			if ((data->map[y][x] == 0 || is_player(data->map[y][x])) && (data->map[y-1][x] == 7 || data->map[y+1][x] == 7 || data->map[y][x-1] == 7 || data->map[y][x+1] == 7 ))
				return (printf(RED"Incorrect Map 1\n"NC));
			if (is_player(data->map[y][x]))
			{
				data->playerx = x + 0.5;
				data->playery = y + 0.5;
				if (data->map[y][x] == 2)
					data->playerr = 90;
				if (data->map[y][x] == 3)
					data->playerr = 180;
				if (data->map[y][x] == 4)
					data->playerr = 270;
				if (data->map[y][x] == 5)
					data->playerr = 0;
				data->map[y][x] = 0;
				player++;
			}
			printf("%d", data->map[y][x]);
		}
		printf("\n");
		x = -1;
	}
	if (player != 1)
		return (printf(RED"Incorrect Number Player\n"NC));
	return (0);
}

int ft_init(int c, char **av, t_data *data)
{
	char *line;

	line = NULL;
	data->ystartmap  = 0;
    if (c != 2)
		return (printf(RED"Error number of arg1\n"NC));	
	data->fdfile = open(av[1], O_RDONLY);
	if (data->fdfile == -1)
		return (printf(RED"Error path of arg2\n"NC));
	data->pathfile = av[1];
	if (ft_init_id(data, &line))
		return (printf(RED"Error in file3\n"NC));
	ft_size_map(data, line);
	printf(ORANGE"\nn = %s\ns = %s\no = %s\ne = %s\n"NC, data->pathnorth, data->pathsouth, data->pathwest, data->patheast);
	printf(ORANGE"\ncolor floor = %d\nr = %d\ng = %d\nb = %d\n"NC, data->floor.color, data->floor.r, data->floor.g, data->floor.b);
	printf(ORANGE"\ncolor sky = %d\nr = %d\ng = %d\nb = %d\n"NC, data->sky.color, data->sky.r, data->sky.g, data->sky.b);
	printf(ORANGE"\nSize mapx = %d\ty = %d start %d\n"NC, data->mapx, data->mapy, data->ystartmap);
	close(data->fdfile);
	if (ft_map(data))
		return (1);
	if (ft_verif_ok_map(data))
		return (1);
	printf(ORANGE"\nPlayer pos\tx = %.2f y %.2f\n"NC, data->playerx, data->playery);
	data->mlx.winx = 1000;
	data->mlx.winy = 1000;
	data->playerfov = 90;
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
		|| y <= 0 || y > data->mlx.winy || x > data->mlx.winx)		// a refaire
		return ;
	// printf("x = %.0f\ty = %.0f\tcolor = %d\n", x, y, color);
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



void ft_color_colone(t_data *data, int x, float len, int color)
{
	int y;

	y = 0;
	while (y < (data->mlx.winy / 2) - (10 / len)*15)
	{
		ft_draw(data, x, y, data->sky.color);
		y++;
	}
	while (y < (data->mlx.winy / 2) + (10 / len)*15)
	{
		ft_draw(data, x, y, color);
		y++;
	}
	while (y < data->mlx.winy)
	{
		ft_draw(data, x, y, data->floor.color);	
		y++;
	}
}

float	ft_absfloat(float nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr); 
}

int ft_ray(t_data *data)
{
	float	i = 0;
	float	angle = 0;
	float	ax = 0;
	float	hyv = 0;
	float	hyr = 0;
	float	posx = 0;
	float	posy = 0;
	float	decalx = 0;
	float	decaly = 0;
	float	length = 0;
	int		face = 0;
	

	angle = data->playerfov / (float)data->mlx.winx;
	// while (i < 700)
	while (i < (float)data->mlx.winx)
	{
		posx = data->playerx;
		posy = data->playery;
		length = 0;
		printf("\n\n\n\t\t----NEW RAY----\n\n\n");
		while (1)
		{

			printf("Start pos Ray x = %.2f y = %.2f len = %.2f\n",posx, posy, length);

			ax =  angle * i + data->playerr - 45;
			if (360 < ax)
				ax = ax - 360;
			else if (ax < 0)
				ax = ax + 360;
			if (0 <= ax && ax <= 90)
			{
				hyv = (posy - (int)posy) / cos((90 - ax) / RAD);
				hyr = (posx - (int)posx) / cos(ax / RAD);
				if (hyv < hyr)
				{
					decaly = (posy - (int)posy) * -1 - 0.001;
					decalx = ((posy - (int)posy) * -1) * tan((90 - ax) / RAD) - 0.001 ;
					length += hyv;
				}
				else
				{
					decaly = ((posx - (int)posx) * -1) * tan((ax) / RAD) - 0.001 ;
					decalx = (posx - (int)posx) * -1 - 0.001;
					length += hyr;
					
				}
			}
			else if (90 < ax && ax < 180)
			{
				hyv = (posy - (int)posy) / cos((90 - ax) / RAD);
				hyr = 1 - (posx - (int)posx) / -cos((180 - ax)  / RAD);
				if (hyv < hyr)
				{
					decaly = ((posy - (int)posy + 0.001) * -1);
					decalx = ((posy - (int)posy)) * tan((90 - ax) / RAD);
					length += hyv;

				}
				else
				{
					decaly = 1 - (posx - (int)posx) * tan((180 - ax)  / RAD);
					decalx = 1 - (posx - (int)posx + 0.001);
					length += hyr;		
				}

				
			}
			// else 
			// {
			// 	printf("ERRORR\n");
			// 	exit(0);
			// }
			if (length < 0)
				length *= -1;
			if (hyr <= hyv)
			{
				face = 1;
				printf(LIGHTRED" %.3f"LIGHTGREEN" %.3f\t%.2f\n"NC, hyr, hyv, ax);

			}
			else
			{
				face = 2;
				printf(LIGHTGREEN" %.3f "LIGHTRED"%.3f\t%.2f\n"NC, hyv, hyr, ax);
			}
			if (5 < decalx)
				decalx = 0;
			if (5 < decaly)
				decaly = 0;
			posx += decalx;
			posy += decaly;
			ft_draw(data, (int)((data->playerx + 1)*20), (int)((data->playery+1)*20),0xffff00);
			ft_draw(data, (int)((posx+1)*20), (int)((posy+1)*20),0xff0000);
			fprintf(stderr, NC"y = %d(%.2f) x = %d(%.2f)\n", (int)floor(posy), posy,  (int)floor(posx), posx);
			if (data->map[((int)floor(posy))][((int)floor(posx))] == 1)
			{
				ft_draw(data, (int)((posx+1)*20), (int)((posy+1)*20),0x0000ff);
				printf("BREAK x = %d(%f) y = %d(%f) len = %.2f\n\n", (int)floor(posx), posx, (int)floor(posy), posy, length);
				break;
			}
		}
		printf("length = %.5f\n\n\n\n", length);
		if (face == 2)
		{
			if (0 < decaly)
				ft_color_colone(data, i, length, 0x0000ff);
			else
				ft_color_colone(data, i, length, 0x00ff00);
		}
		else
		{
			if (0 < decalx)
				ft_color_colone(data, i, length, 0xff0000);
			else
				ft_color_colone(data, i, length, 0xfff000);
		}
		i++;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, data->mlx.i, 0, 0);
	printf("x = %.3fy = %.3f rota = %.3f fov = %d\n", data->playerx, data->playery, data->playerr,data->playerfov);
	}
	return (0);
}
int	ft_key(int keycode, t_data *data)
{
	if (keycode == TOUCH_LEFTARROW)
			data->playerr -= 5;
	else if (keycode == TOUCH_RIGHTARROW)
			data->playerr += 5;
	else if (keycode == TOUCH_W)
			data->playery -= 1;
	else if (keycode == TOUCH_S)
			data->playery += 1;
	else if (keycode == TOUCH_A)
			data->playerx += 1;
	else if (keycode == TOUCH_D)
			data->playerx -= 1;
	else if (keycode == TOUCH_PLUS)
			data->playerfov -= 10;
	else if (keycode == TOUCH_MOINS)
			data->playerfov += 10;
	if (data->playerr < 0)
		data->playerr += 360;
	if (360 < data->playerr)
		data->playerr -= 360;
	if (data->playerfov < 30)
		data->playerfov = 30;
	if (180 < data->playerfov)
		data->playerfov = 180;
	mlx_destroy_image(data->mlx.mlx, data->mlx.i);
	data->mlx.i = mlx_new_image(data->mlx.mlx, data->mlx.winx, data->mlx.winy);
	ft_ray(data);
	return (0);
}

int main(int c, char **av)
{
    t_data data;
    if (ft_init(c, av, &data))
		return (1);
	data.mlx.mlx = mlx_init();
	data.mlx.mlx_win = mlx_new_window(data.mlx.mlx, data.mlx.winx, data.mlx.winy, "Cub3d");
	data.mlx.i = mlx_new_image(data.mlx.mlx, data.mlx.winx, data.mlx.winy);
	data.mlx.data = mlx_get_data_addr(data.mlx.i, &data.mlx.p, &data.mlx.size, &data.mlx.e);
	if (ft_ray(&data))
		return (1);

	mlx_hook(data.mlx.mlx_win, 2, 1L << 0, &ft_key, &data);
	// mlx_hook(m.mlx_win, 17, 1L << 0, &ft_cross_close, &data);
	mlx_loop(data.mlx.mlx);
    return (0);
}