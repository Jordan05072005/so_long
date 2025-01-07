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

int	init(char **argv, t_data **data)
{
	char	**maps;

	maps = parseur(argv[1]);
	if (!maps)
		return (1);
	(*data) = ft_newlist(maps);
	if (!(*data))
		return (1);
	if (loader_character(data, "./assets/soldier.xpm", 2, 0))
		return (1);
	if (loader_other(data))
		return (1);
	build_maps(data);
	(*data)->old_xy[0] = (*data)->xy[0];
	(*data)->old_xy[1] = (*data)->xy[1];
	return (0);
}

int	game_loop2(t_data **d)
{
	char	*nbr;
	char	*button;

	if ((*d)->level == 2
		&& col_player_elem(d, (*d)->xy_exit, HX_EXIT, HY_EXIT))
		close_window(d);
	level(d);
	nbr = ft_itoa((*d)->keys_pressed);
	display((*d)->mlx, (*d)->win, (*d)->bush, 0, 0);
	display((*d)->mlx, (*d)->win, (*d)->bush, 64, 0);
	button = ft_strjoin("button pressed : ", nbr);
	mlx_string_put((*d)->mlx, (*d)->win, 0, 10, 0x00000, button);
	return (free(nbr), free(button), 1);
}

int	game_loop(t_data **d)
{
	if ((*d)->level == 0)
		del_coll(d);
	if ((*d)->etat == 0)
		animation(d, (*d)->idle);
	if ((*d)->etat == 1)
		animation(d, (*d)->att1);
	if ((*d)->etat == 2)
		animation(d, (*d)->att2);
	if ((*d)->etat == 3)
		animation(d, (*d)->damage);
	if ((*d)->etat == 4)
		animation(d, (*d)->death);
	if ((*d)->etat == 5)
		animation(d, (*d)->walk);
	if ((*d)->level == 2)
		animation_static(d, (*d)->exit, 7, (*d)->xy_exit);
	game_loop2(d);
	return (1);
}

int	close_window(t_data **d)
{
	mlx_destroy_window((*d)->mlx, (*d)->win);
	free_data(d);
	mlx_destroy_display((*d)->mlx);
	free((*d)->mlx);
	free((*d));
	ft_putstr_fd("\nGame End\n", 1);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		err;

	if (argc != 2)
		error(2);
	err = init(argv, &data);
	if (err)
		error(1);
	mlx_expose_hook(data->win, build_maps, &data);
	mlx_hook(data->win, 17, 0, close_window, &data);
	mlx_hook(data->win, 2, 1L << 0, key_gestion, &data);
	mlx_loop_hook(data->mlx, game_loop, &data);
	mlx_loop(data->mlx);
}
