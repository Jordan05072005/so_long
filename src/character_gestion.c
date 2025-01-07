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

void	move(int kc, t_data **d)
{
	int	temp[2];

	temp[0] = (*d)->xy[0];
	temp[1] = (*d)->xy[1];
	if (kc == KEY_Z && col(d, -1, 32, '1') && col(d, -1, 0, '1'))
		(*d)->xy[1] -= 16;
	else if (kc == KEY_Q && col(d, 0, -16, '1') && col(d, 32, -16, '1'))
		(*d)->xy[0] -= 16;
	else if (kc == KEY_S && col(d, 48, 0, '1') && col(d, 48, 32, '1'))
		(*d)->xy[1] += 16;
	else if (kc == KEY_D && col(d, 0, 48, '1') && col(d, 32, 48, '1'))
		(*d)->xy[0] += 16;
	else
		return ;
	(*d)->frame = 0;
	(*d)->etat = 5;
	(*d)->old_xy[0] = temp[0];
	(*d)->old_xy[1] = temp[1];
}

int	key_gestion(int keycode, t_data **d)
{
	++(*d)->keys_pressed;
	if (current_anim_fight(*d))
		return (0);
	else if (keycode == KEY_E && !current_anim_fight(*d))
		(*d)->etat = 1;
	else if (keycode == KEY_A && !current_anim_fight(*d))
		(*d)->etat = 2;
	else if (keycode == ESC)
		close_window(d);
	else
		move(keycode, d);
	(*d)->frame = 0;
	return (1);
}
