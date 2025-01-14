/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_gestion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:07:43 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/07 15:07:43 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	set_sens(int kc, t_data **d)
{
	if (kc == KEY_D)
	{
		(*d)->sens = 0;
		(*d)->sens_sprite = 0;
	}
	else if (kc == KEY_Q)
	{
		(*d)->sens = 1;
		(*d)->sens_sprite = 1;
	}
	else if (kc == KEY_Z)
		(*d)->sens = 2;
	else if (kc == KEY_S)
		(*d)->sens = 3;
	else
		return ;
	(*d)->old_sens = (*d)->sens;
}

void	move(int kc, t_data **d)
{
	int	t[2];

	t[0] = (*d)->xy[0];
	t[1] = (*d)->xy[1];
	if ((*d)->level == 1 && col_beforemove(d,
			(*d)->xy_mob, HX_MOB * 2, HY_MOB * 2))
		return (damage_player(d));
	if (kc == KEY_Z && col(d, -1, 32, t) && col(d, -1, 0, t))
		(*d)->xy[1] -= 16;
	else if (kc == KEY_Q && col(d, 0, -16, t) && col(d, 32, -16, t))
		(*d)->xy[0] -= 16;
	else if (kc == KEY_S && col(d, 48, 0, t) && col(d, 48, 32, t))
		(*d)->xy[1] += 16;
	else if (kc == KEY_D && col(d, 0, 48, t) && col(d, 32, 48, t))
		(*d)->xy[0] += 16;
	else
		return ;
	(*d)->frame = 0;
	(*d)->etat = 5;
	(*d)->xy[2] = t[0];
	(*d)->xy[3] = t[1];
}

int	key_gestion(int keycode, t_data **d)
{
	++(*d)->keys_pressed;
	if (keycode == ESC)
		return (close_window(d, "Game end\n"));
	else if (current_anim_fight(*d))
		return (0);
	else if (keycode == KEY_E && !current_anim_fight(*d))
		(*d)->etat = 1;
	else if (keycode == KEY_A && !current_anim_fight(*d))
		(*d)->etat = 2;
	set_sens(keycode, d);
	move(keycode, d);
	(*d)->frame = 0;
	return (1);
}
