/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_maps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:08:10 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/07 15:08:10 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	build2(t_data **d, int x, int y, int *i)
{
	if ((*d)->maps[y][x] == collectible)
	{
		fill_co((*d)->xy_c[(*i)], x * 64 + 10, y * 64 + 10);
		display((*d)->mlx, (*d)->win, (*d)->coll, x * 64 + 10, y * 64 + 10);
		(*i)++;
	}
	if ((*d)->maps[y][x] == player)
	{
		fill_co((*d)->xy, x * 64, y * 64);
		display((*d)->mlx, (*d)->win, (*d)->idle[0], x * 64, y * 64);
	}
}

int	build_maps(t_data **d)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = -1;
	while ((*d)->maps[++y])
	{
		x = -1;
		while ((*d)->maps[y][++x])
		{
			if ((*d)->maps[y][x] == wall)
				display((*d)->mlx, (*d)->win, (*d)->bush, x * 64, y * 64);
			else
				display((*d)->mlx, (*d)->win, (*d)->grass, x * 64, y * 64);
			if ((*d)->maps[y][x] == exits)
				fill_co((*d)->xy_exit, x * 64 + SX_EXIT, y * 64 + SY_EXIT);
			build2(d, x, y, &i);
		}
	}
	(*d)->xy_c[i] = 0;
	(*d)->xy_c[i] = 0;
	return (1);
}

int	*find_coo(t_data **d, char find)
{
	int	x;
	int	y;
	int	*co;

	co = malloc(sizeof(int) * 2);
	y = -1;
	while ((*d)->maps[++y])
	{
		x = -1;
		while ((*d)->maps[y][++x])
		{
			if ((*d)->maps[y][x] == find)
			{
				co[0] = x * 64;
				co[1] = y * 64;
				return (co);
			}
		}
	}
	return (0);
}