/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 02:08:24 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/14 02:08:24 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	cpy(t_data **data)
{
	int	temp;

	(*data)->s_a[0] = 6;
	(*data)->s_a[1] = 5;
	(*data)->s_a[2] = 6;
	(*data)->s_a[3] = 4;
	(*data)->s_a[4] = 4;
	(*data)->s_a[5] = 8;
	(*data)->xy_mob[0] = -1;
	(*data)->xy_mob[1] = -1;
	(*data)->etat = 0;
	(*data)->life = 3;
	(*data)->sens_sprite = 0;
	(*data)->level = 0;
	(*data)->keys_pressed = 0;
	(*data)->frame = 0;
	(*data)->frame2 = 0;
	temp = strlenchar((*data)->maps, 'C');
	(*data)->xy_c = malloc(sizeof(int *) * (temp + 1));
	(*data)->xy_c[temp] = 0;
	while (--temp >= 0)
		(*data)->xy_c[temp] = malloc(sizeof(int) * 2);
}

t_data	*ft_newlist(char **maps)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (NULL);
	data->lenght = ft_strlen(maps[0]);
	data->height = ft_strstrlen(maps);
	data->win = mlx_new_window(data->mlx, data->lenght * 64,
			data->height * 64, "so_long");
	if (!data->win)
		return (NULL);
	data->maps = maps;
	data->etat = 0;
	cpy(&data);
	return (data);
}
