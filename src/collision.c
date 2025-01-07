/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 01:32:56 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/04 01:32:56 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

//Collision élément décor et player
int	col(t_data **d, int y, int x, char obj)
{
	if ((*d)->maps[((*d)->xy[1] + y) / 64][((*d)->xy[0] + x) / 64] != obj)
		return (1);
	return (0);
}

//Collision entre tout les collectible et le player
int	col_player_coins(t_data **d, int s1, int s2, int s3)
{
	int	i;

	i = -1;
	while ((*d)->xy_c[++i] != 0)
	{
		if ((*d)->xy[0] < (*d)->xy_c[i][0] + s3
			&& (*d)->xy[0] + s1 > (*d)->xy_c[i][0]
			&& (*d)->xy[1] < (*d)->xy_c[i][1] + s3
			&& (*d)->xy[1] + s2 > (*d)->xy_c[i][1])
			return (i);
	}
	return (-1);
}

//Collision entre player et un élément a hitbox variable 
int	col_player_elem(t_data **d, int *xy, int x2, int y2)
{
	int	p1;
	int	p2;

	p1 = 48;
	p2 = 32;
	if ((*d)->xy[0] < xy[0] + x2 && (*d)->xy[0] + p1 > xy[0]
		&& (*d)->xy[1] < xy[1] + y2 && (*d)->xy[1] + p2 > xy[1])
		return (1);
	return (0);
}