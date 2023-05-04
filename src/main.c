/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/04 14:22:29 by ngriveau         ###   ########.fr       */
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
	// printf("path = |%s|\n", *path_for_data);
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
	x = -1;
	y = -1;
	while (++y < data->mapy)
	{
		while (++x < data->mapx)
			printf("%d", data->map[y][x]);
		x = -1;
		printf("\n");
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
			if (is_player(data->map[y][x]))
				player++;
			if ((y == 0 || x == 0 || y == data->mapy - 1 || x == data->mapx - 1) && (data->map[y][x] == 0 || is_player(data->map[y][x])) )
				return (1);
			if ((data->map[y][x] == 0 || is_player(data->map[y][x]))&& (data->map[y-1][x] == 7 || data->map[y+1][x] == 7 || data->map[y][x-1] == 7 || data->map[y][x+1] == 7 ))
				return (1);
				
		}
		x = -1;
	}
	if (player != 1)
		return (1);
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
		return (printf(RED"Error 2\n"NC));
	
	return (0);
}

int main(int c, char **av)
{
    t_data data;
    if (ft_init(c, av, &data))
		return (1);
    return (0);
}