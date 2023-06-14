/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/14 16:10:43 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

int	is_ws(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
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
	// gettimeofday(&tv, NULL);
	// return (tv.tv_usec + tv.tv_sec * 1000000);

long long	ft_get_time(void)
{
	static struct timeval	tv;

	(void) tv;
	return (12);
}

void	ft_fps(t_data *data, long long fps)
{
	char		*str;
	long long	endfps;

	endfps = ft_get_time();
	if (endfps == fps)
		return ;
	str = ft_itoa((1000000 / (int)(endfps - fps)));
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 10, \
		data->mlx.winy - 10, 0xffffff, "FPS:");
	mlx_string_put(data->mlx.mlx, data->mlx.mlx_win, 35, \
		data->mlx.winy - 10, 0xffffff, str);
	free(str);
}
