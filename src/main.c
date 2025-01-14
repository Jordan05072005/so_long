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
	if (loader_character(data, "./assets/soldierg.xpm", 2, 1))
		return (1);
	if (loader_mob(data))
		return (1);
	if (loader_other(data))
		return (1);
	build_maps(data);
	(*data)->xy[2] = (*data)->xy[0];
	(*data)->xy[3] = (*data)->xy[1];
	return (0);
}

int	game_loop2(t_data **d)
{
	char	*nbr;
	char	*button;

	level(d);
	nbr = ft_itoa((*d)->keys_pressed);
	mlx_put_image_to_window((*d)->mlx, (*d)->win, (*d)->bush, 0, 0);
	mlx_put_image_to_window((*d)->mlx, (*d)->win, (*d)->bush, 64, 0);
	button = ft_strjoin("button pressed : ", nbr);
	mlx_string_put((*d)->mlx, (*d)->win, 0, 10, 0x00000, button);
	(*d)->sens = -1;
	return (free(nbr), free(button), 1);
}

int	game_loop(t_data **d)
{
	if ((*d)->level == 0
		&& col_player_coins(d, HX_PLAYER * 2, HX_PLAYER * 2, HX_COLL * 2) != -1)
		delete(d, COLLECTIBLE);
	if (col_fight(d, (*d)->xy_mob, HX_MOB * 2, HY_MOB * 2)
		&& current_anim_fight(*d) && (*d)->frame == 4 * SECONDE)
		delete(d, MOB);
	if ((*d)->level == 1 && (*d)->xy_mob[0] != -1)
		move_mob(d);
	if ((*d)->level == 2
		&& col_player_elem(d, (*d)->xy_exit, HX_EXIT, HY_EXIT))
		close_window(d, "Vous avez Gagner !! \n");
	animation_gestion(d);
	if ((*d)->life <= 0 && (*d)->frame == 0)
		close_window(d, "C'est Perdu, réessaie !\n");
	game_loop2(d);
	return (1);
}

int	close_window(t_data **d, char *message)
{
	mlx_destroy_window((*d)->mlx, (*d)->win);
	free_data(d);
	mlx_destroy_display((*d)->mlx);
	free((*d)->mlx);
	free((*d));
	if (message)
		ft_putstr_fd(message, 1);
	else
		ft_putstr_fd("Game End", 1);
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
