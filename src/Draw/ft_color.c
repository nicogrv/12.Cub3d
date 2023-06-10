/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/10 12:55:56 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"

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
#include <sys/time.h>

long long	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec + tv.tv_sec * 1000000);
}

void	ft_color_colone(t_data *data, int x, float len, int pcofwall)
{
	int				wall;
	static int		saveface;
	static float	savelen = {0};
	long long		time;
	
	time = ft_get_time();
	data->y = 0;
	if (pcofwall == 100)
		pcofwall = 99;
	if ((5 < pcofwall && pcofwall < 95) || (fabs(savelen - len) > 0.1))
		saveface = data->face;
if (x == 1) printf("1 = %lld\n", ft_get_time()-time);
	if ((fabs(savelen - len) < 0.4) && ((pcofwall <= 1 && (data->face == 4 || \
data->face == 2)) || (pcofwall >= 98 && (data->face == 1 || data->face == 3))))
		data->face = saveface;
	wall = (data->mlx.winy / 2) + (10 / len) * data->lenwall - \
		((data->mlx.winy / 2) - (10 / len) * data->lenwall);
if (x == 1) printf("2 = %lld\n", ft_get_time()-time);
	if (data->mlx.winy < wall)
		data->y = data->mlx.winy - wall;
	while (data->y < (data->mlx.winy / 2) - (10 / len) * data->lenwall)
		ft_draw(data, x, data->y++, data->sky.color);
	data->nbrpl = data->y;
if (x == 1) printf("3 = %lld\n", ft_get_time()-time);
	while (data->y < (data->mlx.winy / 2) + (10 / len) * data->lenwall)
		ft_draw(data, x, data->y, ft_pixel_of_img(data, data->face, pcofwall, \
				((data->y - data->nbrpl) * 100 / wall)));
if (x == 1) printf("4 = %lld\n", ft_get_time()-time);
	while (data->y < data->mlx.winy)
		ft_draw(data, x, data->y++, data->floor.color);
	savelen = len;
if (x == 1) printf("5 = %lld\n", ft_get_time()-time);

}
