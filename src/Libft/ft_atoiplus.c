/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoiplus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:21:17 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/09 00:06:29 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_atoiplus_pt2(char *str, int i, long nb, int signe)
{
	int	index;

	index = i;
	while ('0' <= str[i] && str[i] <= '9')
		nb = nb * 10 + str[i++] - 48;
	if (str[i] == '\0' && 0 <= (nb * signe)
		&& (nb * signe) <= 255 && (i - index) < 15)
		return (nb * signe);
	return (-1);
}

int	ft_atoiplus(char *str)
{	
	int		i;
	int		signe;
	long	nb;

	signe = 1;
	i = 0;
	nb = 0;
	if (!str[i])
		return (-1);
	while (('\t' <= str[i] && str[i] <= '\r') || (str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		i++;
		signe = -signe;
	}
	if (ft_isdigit(str[i]) == 0)
		return (-1);
	return (ft_atoiplus_pt2(str, i, nb, signe));
}
