/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:11:55 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/13 05:11:55 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	strlenchar(char **str, char find)
{
	int	i;
	int	j;
	int	compt;

	i = 0;
	compt = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == find)
				compt++;
			j++;
		}
		i++;
	}
	return (compt);
}

//Collision élément décor et player
int	col(t_data *d, int y, int x, char obj)
{
	if (d->maps[(d->xy[1] + y) / 64][(d->xy[0] + x) / 64] != obj)
		return(1);
	return (0);
}

//Collision etre deux hitbox
int	col_hitbox(int xy1[2], int xy2[2], int s1, int s2)
{
	if (xy1[0] < xy2[0] + s2 && xy1[0] + s1 > xy2[0]
		&& xy1[1] < xy2[1] + s2 && xy1[1] + s1 > xy2[1])
		return (1);
	return (0);
}

int	current_anim_fight(t_data *d)
{
	if (d->etat == 1 || d->etat == 2 && d->frame != 0)
		return (1);
	return (0);
}
