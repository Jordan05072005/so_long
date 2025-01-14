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
		display((*d)->mlx, (*d)->win, (*d)->grassp, (*d)->xy[2],
			(*d)->xy[3]);
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

void	animation_static(t_data **d, void **img, int size, int *xy)
{
	if ((*d)->frame2 % SECONDE == 0)
	{
		display((*d)->mlx, (*d)->win, (*d)->grassp, xy[2],
			xy[3]);
		display((*d)->mlx, (*d)->win, img[((*d)->frame2 / SECONDE)],
			xy[0], xy[1]);
	}
	(*d)->frame2++;
	if ((*d)->frame2 >= size * SECONDE)
		(*d)->frame2 = 0;
	return ;
}

void	animation_gestion(t_data **d)
{
	if ((*d)->life > 0)
	{
		if ((*d)->etat == 0)
			animation(d, (*d)->idle[(*d)->sens_sprite]);
		else if ((*d)->etat == 1)
			animation(d, (*d)->att1[(*d)->sens_sprite]);
		else if ((*d)->etat == 2)
			animation(d, (*d)->att2[(*d)->sens_sprite]);
		else if ((*d)->etat == 3)
			animation(d, (*d)->damage[(*d)->sens_sprite]);
		else if ((*d)->etat == 5)
			animation(d, (*d)->walk[(*d)->sens_sprite]);
	}
	else if ((*d)->life <= 0)
		animation(d, (*d)->death[(*d)->sens_sprite]);
	if ((*d)->level == 1 && (*d)->xy_mob[0] != -1)
		animation_static(d, (*d)->mobs, 4, (*d)->xy_mob);
	if ((*d)->level == 2)
		animation_static(d, (*d)->exit, 7, (*d)->xy_exit);
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
	else if ((*d)->level == 1 && (*d)->xy_mob[0] == -1)
		(*d)->level = 2;
}

void	delete(t_data **d, char select)
{
	int	i;

	if (select == collectible)
	{
		i = col_player_coins(d, HX_PLAYER * 2, HX_PLAYER * 2, HX_COLL * 2);
		display((*d)->mlx, (*d)->win, (*d)->grassp,
			(*d)->xy_c[i][0], (*d)->xy_c[i][1]);
		(*d)->xy_c[i][0] = -1;
		(*d)->xy_c[i][1] = -1;
	}
	if (select == mob)
	{
		display((*d)->mlx, (*d)->win, (*d)->grassp,
			(*d)->xy_mob[0] - SX_MOB, (*d)->xy_mob[1] - SY_MOB);
		(*d)->xy_mob[0] = -1;
		(*d)->xy_mob[1] = -1;
	}
}
