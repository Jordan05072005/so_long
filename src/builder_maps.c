/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 01:49:48 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/14 01:49:48 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int build2(t_data **d, int x, int y, int *i)
{
	if ((*d)->maps[y][x] == 'C')
	{
		(*d)->xy_c[(*i)][0] = x * 64 + 10;
		(*d)->xy_c[(*i)][1] = y * 64 + 10;
		display((*d)->mlx, (*d)->win, (*d)->coll[0], x * 64 + 10, y * 64 + 10);
		(*i)++;
	}
	if ((*d)->maps[y][x] == 'P')
	{
		(*d)->xy[0] = x * 64;
		(*d)->xy[1] = y * 64;
		display((*d)->mlx, (*d)->win, (*d)->idle[0][0], x * 64, y * 64);
	}
}

int build_maps(t_data **d)
{
	int	x;
	int	y;
	int	i;
	int	temp;

	i = 0;
	y = -1;
	while ((*d)->maps[++y])
	{
		x = -1;
		while ((*d)->maps[y][++x])
		{
			if ((*d)->maps[y][x] == '1')
				display((*d)->mlx, (*d)->win, (*d)->bush, x * 64, y * 64);
			else
				display((*d)->mlx, (*d)->win, (*d)->grass, x * 64, y * 64);
			build2(d, x, y, &i);
		}
	}
	(*d)->xy_c[i] = 0;
	(*d)->xy_c[i] = 0;
}
