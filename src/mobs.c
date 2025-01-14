/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:59:16 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/13 01:59:16 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	aggro(t_data **d)
{
	if ((*d)->xy_mob[0] - AGGRO > (*d)->xy[0] + HX_PLAYER
		|| (*d)->xy_mob[0] + HX_MOB + AGGRO < (*d)->xy[0]
		|| (*d)->xy_mob[1] - AGGRO > (*d)->xy[1] + HX_PLAYER
		|| (*d)->xy_mob[1] + HX_MOB + AGGRO < (*d)->xy[1])
		(*d)->aggro = 1;
	else if ((*d)->xy[1] + HX_PLAYER < (*d)->xy_mob[1])
		(*d)->aggro = 3;
	else if ((*d)->xy[1] > (*d)->xy_mob[1] + HY_MOB)
		(*d)->aggro = 7;
	else if ((*d)->xy[0] > (*d)->xy_mob[0] + HX_MOB)
		(*d)->aggro = 2;
	else if ((*d)->xy[0] + HX_PLAYER < (*d)->xy_mob[0])
		(*d)->aggro = 5;
}

void	move_mob(t_data **d)
{
	int	t[2];

	aggro(d);
	t[0] = (*d)->xy_mob[0];
	t[1] = (*d)->xy_mob[1];
	if (col(d, 0, 48 + 16, (*d)->xy_mob) && (*d)->frame2 == 0
		&& col(d, HY_MOB, 48 + 16, (*d)->xy_mob) && 2 % (*d)->aggro == 0)
		(*d)->xy_mob[0] += 16;
	else if (col(d, HY_MOB - 16, 0, (*d)->xy_mob) && (*d)->frame2 == 0
		&& col(d, HY_MOB - 16, HX_MOB, (*d)->xy_mob) && 3 % (*d)->aggro == 0)
		(*d)->xy_mob[1] -= 16;
	else if (col(d, 0, -16, (*d)->xy_mob) && (*d)->frame2 == 0
		&& col(d, HY_MOB, -16, (*d)->xy_mob) && 5 % (*d)->aggro == 0)
		(*d)->xy_mob[0] -= 16;
	else if (col(d, HY_MOB + 16, 0, (*d)->xy_mob) && (*d)->frame2 == 0
		&& col(d, HY_MOB + 16, HX_MOB, (*d)->xy_mob) && 7 % (*d)->aggro == 0)
		(*d)->xy_mob[1] += 16;
	if (col_player_elem(d, (*d)->xy_mob, HX_MOB * 2, HY_MOB * 2))
	{
		(*d)->xy_mob[0] = t[0];
		(*d)->xy_mob[1] = t[1];
	}
	(*d)->xy_mob[2] = t[0];
	(*d)->xy_mob[3] = t[1];
}

void	damage_player(t_data **d)
{
	if (col_beforemove(d, (*d)->xy_mob, HX_MOB * 2, HY_MOB * 2)
		|| col_player_elem(d, (*d)->xy_mob, HX_MOB * 2, HY_MOB * 2))
	{
		(*d)->life--;
		(*d)->etat = 3;
	}
}
