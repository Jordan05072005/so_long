/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 04:51:28 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/13 04:51:28 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	loader_character2(t_data **d)
{
	int	i;

	i = -1;
	while (++i < 6)
		crop_img(d, &(*d)->att1[i], i * 100 + SX_P, 2 * 100 + SY_P);
	i = -1;
	while (++i < 6)
		crop_img(d, &(*d)->att2[i], i * 100 + SX_P, 3 * 100 + SY_P);
	i = -1;
	while (++i < 4)
		crop_img(d, &(*d)->damage[i], i * 100 + SX_P, 4 * 100 + SY_P);
	i = -1;
	while (++i < 4)
		crop_img(d, &(*d)->death[i], i * 100 + SX_P, 5 * 100 + SY_P);
	mlx_destroy_image((*d)->mlx, (*d)->img);
	(*d)->img = NULL;
	(*d)->data[0] = NULL;
	return (0);
}

int	loader_character(t_data **d, char *path, int scale, int t)
{
	int	img_width;
	int	img_height;
	int	i;

	i = -1;
	(*d)->scale = scale;
	(*d)->size = HX_PLAYER;
	(*d)->type = t;
	(*d)->img = mlx_xpm_file_to_image((*d)->mlx, path, &img_width, &img_height);
	if (!(*d)->img)
		return (1);
	(*d)->data[0] = mlx_get_data_addr((*d)->img, &(*d)->bpp[0],
			&(*d)->size_line[0], &(*d)->endian[0]);
	while (++i < 6)
		crop_img(d, &(*d)->idle[i], i * 100 + SX_P, 0 * 100 + SY_P);
	i = -1;
	while (++i < 8)
		crop_img(d, &(*d)->walk[i], i * 100 + SX_P, 1 * 100 + SY_P);
	i = -1;
	loader_character2(d);
	return (0);
}

int	loader_other2(t_data **d, int w, int h)
{
	int	i;

	i = -1;
	if (!(*d)->img)
		return (1);
	(*d)->data[0] = mlx_get_data_addr((*d)->img, &(*d)->bpp[0],
			&(*d)->size_line[0], &(*d)->endian[0]);
	crop_img(d, &(*d)->coll, HX_COLL, 0);
	mlx_destroy_image((*d)->mlx, (*d)->img);
	(*d)->img = mlx_xpm_file_to_image((*d)->mlx, "./assets/portal.xpm", &w, &h);
	if (!(*d)->img)
		return (1);
	(*d)->scale = 1;
	(*d)->size = HY_EXIT;
	(*d)->data[0] = mlx_get_data_addr((*d)->img, &(*d)->bpp[0],
			&(*d)->size_line[0], &(*d)->endian[0]);
	while (++i < 7)
		crop_img(d, &(*d)->exit[i], i * 64 + SX_EXIT, SY_EXIT);
	mlx_destroy_image((*d)->mlx, (*d)->img);
	return (0);
}

int	loader_other(t_data **d)
{
	int	w;
	int	h;

	(*d)->grass = mlx_xpm_file_to_image((*d)->mlx,
			"./assets/grass.xpm", &w, &h);
	if (!(*d)->grass)
		return (1);
	(*d)->bush = mlx_xpm_file_to_image((*d)->mlx,
			"./assets/bush.xpm", &w, &h);
	if (!(*d)->bush)
		return (1);
	(*d)->grassp = mlx_xpm_file_to_image((*d)->mlx,
			"./assets/grassp.xpm", &w, &h);
	if (!(*d)->grassp)
		return (1);
	(*d)->scale = 2;
	(*d)->size = HX_COLL;
	(*d)->img = mlx_xpm_file_to_image((*d)->mlx,
			"./assets/coll.xpm", &w, &h);
	loader_other2(d, w, h);
	return (0);
}
