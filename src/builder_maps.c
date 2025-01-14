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
	if ((*d)->maps[y][x] == COLLECTIBLE)
	{
		fill_co((*d)->xy_c[(*i)], x * 64 + 10, y * 64 + 10);
		mlx_put_image_to_window((*d)->mlx, (*d)->win,
			(*d)->coll, x * 64 + 10, y * 64 + 10);
		(*i)++;
	}
	if ((*d)->maps[y][x] == PLAYER)
	{
		fill_co((*d)->xy, x * 64, y * 64);
		mlx_put_image_to_window((*d)->mlx, (*d)->win,
			(*d)->idle[0][0], x * 64, y * 64);
	}
	if ((*d)->maps[y][x] == MOB)
	{
		fill_co((*d)->xy_mob, x * 64 + SX_MOB, y * 64 + SY_MOB);
		if ((*d)->level == 1)
			mlx_put_image_to_window((*d)->mlx, (*d)->win, (*d)->mobs[0],
				x * 64 + SX_MOB, y * 64 + SY_MOB);
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
			if ((*d)->maps[y][x] == WALL)
				mlx_put_image_to_window((*d)->mlx, (*d)->win,
					(*d)->bush, x * 64, y * 64);
			else
				mlx_put_image_to_window((*d)->mlx, (*d)->win,
					(*d)->grass, x * 64, y * 64);
			if ((*d)->maps[y][x] == EXITS)
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

int	close_windows(t_data **d)
{
	close_window(d, NULL);
	return (1);
}
