/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:21:17 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/03 17:55:11 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_isdigit(int c)
{	
	if (('0' <= c && c <= '9') || c == '-' || c == '+')
		return (1);
	return (0);
}

/*int main(void)
{
	int i = 0;
	while (i<127)
	{
		printf("%d \t", isdigit(i));
		printf("%d \t %c\n\n", ft_isdigit(i),i);
		i++;
	}
}*/
