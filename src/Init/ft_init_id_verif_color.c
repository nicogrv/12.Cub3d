/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_id_verif_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/30 11:17:37 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./_Include/cub3d.h"

void	ft_init_id_verif_color_pt4(char *tmp, t_color *color)
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

int	ft_init_id_verif_color_pt3(char *tmp, int *j, char *line, t_color *c)
{
	while (1)
	{
		tmp = ft_substr(line, *j, ft_strlen_mode(line + *j, 2));
		if (!tmp)
			return (free(tmp), printf("SORT 1\n"), 1);
		if (c->id == 0 || c->id == 1 || c->id == 2)
			ft_init_id_verif_color_pt4(tmp, c);
		else
		{
			if (c->r == -1 || c->g == -1 || c->b == -1)
				return (free(tmp), printf(RED"Error input color3"NC), 1);
			return (free(tmp), 0);
		}
		free(tmp);
		*j += ft_strlen_mode(line + *j, 2) + 1;
	}
}

int	ft_init_id_verif_color_pt2(int i, int *id, char *line, int *j)
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
	if (ft_init_id_verif_color_pt3(tmp, &j, line, color))
		return (1);
	color->color = (color->r * 65536) + (color->g * 256) + color->b;
	while (is_ws(line[j]))
		j++;
	if (line[j] == '\n' || line[j] == '\0')
		return (0);
	return (1);
}
