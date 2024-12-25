/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 04:07:20 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/13 04:07:20 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	init(int argc, char **argv, t_data **data)
{
	char **maps;

	maps = parseur(argv[1]); // check si c'est finisable 
	if (!maps)
		return (1);
	(*data) = ft_newlist(maps);
	if (!(*data))
		return (1);
	if (loader_other(data, "./assets/grass.xpm", "./assets/bush.xpm", "./assets/coll.xpm", "./assets/grassp.xpm")
			// || loader_character(data, "./assets/orc.xpm", 2, 1)
			||loader_character(data, "./assets/soldier.xpm", 2, 0))
		return (1);
	build_maps(data);
	(*data)->old_xy[0] = (*data)->xy[0] ;
	(*data)->old_xy[1] = (*data)->xy[1] ;
	return (0);
}

int game_loop(t_data **d)
{
	int	i;

	i = -1;
	while ((*d)->xy_c[++i] != 0)
	{
		if (col_hitbox((*d)->xy, (*d)->xy_c[i], 50, 16))
		{
			display((*d)->mlx, (*d)->win, (*d)->grass,
				(*d)->xy_c[i][0] - 10, (*d)->xy_c[i][1] - 10);
			(*d)->xy_c[i][0] = -1;
			(*d)->xy_c[i][1] = -1;
		}
	}
	if ((*d)->etat == 0)
		animation(d, (*d)->idle[0]);
	if ((*d)->etat == 1)
		animation(d, (*d)->att1[0]);
	if ((*d)->etat == 2)
		animation(d, (*d)->att2[0]);
	if ((*d)->etat == 3)
		animation(d, (*d)->damage[0]);
	if ((*d)->etat == 4)
		animation(d, (*d)->death[0]);
	if ((*d)->etat == 5)
		animation(d, (*d)->walk[0]);
}

int	close_window(t_data **d)
{
	mlx_destroy_window((*d)->mlx, (*d)->win);
	free_data(d);
	mlx_destroy_display((*d)->mlx);
	free((*d)->mlx);
	free((*d));
	exit(0);
}

int main(int argc, char **argv)
{
	t_data *data;
	int err;

	if (argc != 2)
		return (1);
	err = init(argc, argv, &data);
	if (err)
		return(1);
	mlx_expose_hook(data->win, build_maps, &data);
	mlx_hook(data->win, 17, 0, close_window, &data);
	mlx_hook(data->win, 2, 1L << 0, key_gestion, &data);
	mlx_loop_hook(data->mlx, game_loop, &data);
	mlx_loop(data->mlx);
}
