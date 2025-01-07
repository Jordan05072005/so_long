/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:32:30 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/27 13:32:30 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	animation(t_data **d, void **img)
{
	if ((*d)->frame % SECONDE == 0)
	{
		display((*d)->mlx, (*d)->win, (*d)->grassp, (*d)->old_xy[0],
			(*d)->old_xy[1]);
		display((*d)->mlx, (*d)->win, img[((*d)->frame / SECONDE)],
			(*d)->xy[0], (*d)->xy[1]);
	}
	(*d)->frame++;
	if ((*d)->frame >= (*d)->s_a[(*d)->etat] * SECONDE)
	{
		(*d)->frame = 0;
		(*d)->etat = 0;
	}
	return ;
}

void	animation_static(t_data **d, void **img, int size, int xy[2])
{
	if ((*d)->frame2 % SECONDE == 0)
	{
		display((*d)->mlx, (*d)->win, (*d)->grassp, xy[0],
			xy[1]);
		display((*d)->mlx, (*d)->win, img[((*d)->frame2 / SECONDE)],
			xy[0], xy[1]);
	}
	(*d)->frame2++;
	if ((*d)->frame2 >= size * SECONDE)
		(*d)->frame2 = 0;
	return ;
}

void	level(t_data **d)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if ((*d)->level == 0)
	{
		while ((*d)->xy_c[++i] != 0)
			if ((*d)->xy_c[i][0] == -1)
				j++;
		if ((*d)->xy_c[j] == 0)
			(*d)->level = 1;
	}
	else if ((*d)->level == 1)
		(*d)->level = 2;
}

void	del_coll(t_data **d)
{
	int	i;

	i = col_player_coins(d, HX_PLAYER * 2, HX_PLAYER * 2, HX_COLL * 2);
	if (i != -1)
	{
		display((*d)->mlx, (*d)->win, (*d)->grassp,
			(*d)->xy_c[i][0], (*d)->xy_c[i][1]);
		(*d)->xy_c[i][0] = -1;
		(*d)->xy_c[i][1] = -1;
	}
}
