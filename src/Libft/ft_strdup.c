/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:39:56 by ngriveau          #+#    #+#             */
/*   Updated: 2023/05/03 15:18:05 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/cub3d.h"


char	*ft_strdup(char *str)
{
	int		i;
	char	*dup;

	i = 0;
	while (str[i] != '\0')
		i++;
	dup = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// int main (void)
// {
//     //char *test = "Bonjoujcsyfjwgfwr les \n amis";
// 	char * s = ft_strdup((char*)"coucou");
// 	char * a = strdup((char*)"coucou");
//     printf("ft%d |%d||%d|\n", strcmp(s, "coucou"), s[5], s[6]);
//     printf("st%d |%d||%d|", strcmp(a, "coucou"), a[5], a[6]);
//     return(0);
// }