/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/14 14:37:01 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

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
	char	*line;

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
		if (line[x] == ' ' || line[x] == '0' || line[x] == '1' || \
	line[x] == 'N' || line[x] == 'E' || line[x] == 'S' || line[x] == 'O')
			ft_map_pt3(data, *y, x, line);
		else if (line[x] == '\n')
			break ;
		else
			return (free(line), 1);
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
			return (close(fd), ft_free_map(data, y + 1), 1);
	}
	close(fd);
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
