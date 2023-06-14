/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:21:17 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/14 16:01:16 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_isdigit(int c)
{	
	if (('0' <= c && c <= '9') || c == '-' || c == '+')
		return (1);
	return (0);
}

