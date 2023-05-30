/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/30 11:13:51 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/cub3d.h"

int	ft_init_id_pt5(t_data *data, int id)
{
	if (!data->east.path || !data->west.path || !data->south.path || \
				!data->north.path || id != 6)
		return (ft_free_path_tex(data), 1);
	else
		return (0);
}

int	ft_init_id_pt4(t_data *data, char *li, int *id, int i)
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

int	ft_init_id_pt3(t_data *data, char *li, int *id, int i)
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
