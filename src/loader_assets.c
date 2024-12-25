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

void	crop_img2(t_data **d, int scale, char *src, int *v)
{
	char	*dest;
	unsigned int	color;

	while (++v[2] < scale)
	{
		v[3] = -1;
		while (++v[3] < scale)
		{
			dest = (*d)->data[1] + ((v[1] * scale + v[2])
					* (*d)->size_line[1] + (v[0] * scale + v[3])
					* ((*d)->bpp[1] / 8));
			color = *(unsigned int *)src;
			if ((color & 0xFF000000) == 0x00000000) //if (color != 0x3E8948)
				*(unsigned int *)dest = color;
		}
	}
}

void	crop_img(t_data **d, void **img, int x_start, int y_start)
{
	int		v[4];
	char	*src;
	int		size;
	int scale;

	scale = (*d)->scale;
	size = (*d)->size;
	v[0] = -1;
	*img = mlx_new_image((*d)->mlx, size * scale, size * scale);
	(*d)->data[1] = mlx_get_data_addr(*img, &(*d)->bpp[1],
			&(*d)->size_line[1], &(*d)->endian[1]);
	while (++v[0] < size)
	{
		v[1] = -1;
		while (++v[1] < size)
		{
			src = (*d)->data[0] + ((v[1] + y_start) * (*d)->size_line[0]
					+ (v[0] + x_start) * ((*d)->bpp[0] / 8));
			v[2] = -1;
			crop_img2(d, scale, src, v);		
		}
	}
	(*d)->data[1] = NULL;
}

int	loader_character(t_data **d, char *path, int scale, int t)
{
	int x_y[2] = {0, 0};
	int img_width;
	int img_height;
	int i;

	i = -1;
	(*d)->scale = scale;
	(*d)->size = 25;
	(*d)->type = t;
	(*d)->img = mlx_xpm_file_to_image((*d)->mlx, path, &img_width, &img_height);
	if (!(*d)->img)
		return (1);
	(*d)->data[0] = mlx_get_data_addr((*d)->img, &(*d)->bpp[0], &(*d)->size_line[0], &(*d)->endian[0]);
	while (++i < 6)
		crop_img(d, &(*d)->idle[t][i], i * 100 + 35, 0 * 100 + 35);
	i = -1;
	while (++i < 8)
		crop_img(d, &(*d)->walk[t][i], i * 100 + 35, 1 * 100 + 35);
	i = -1;
	while (++i < 6)
		crop_img(d, &(*d)->att1[t][i], i * 100 + 35, 2 * 100 + 35);
	i = -1;
	while (++i < 6)
		crop_img(d, &(*d)->att2[t][i], i * 100 + 35, 3 * 100 + 35);
	i = -1;
	while (++i < 4)
		crop_img(d, &(*d)->damage[t][i], i * 100 + 35, 4 * 100 + 35);
	i = -1;
	while (++i < 4)
		crop_img(d, &(*d)->death[t][i], i * 100 + 35, 5 * 100 + 35);
	mlx_destroy_image((*d)->mlx, (*d)->img);
	(*d)->img = NULL; // erreur ici ca seg 
	(*d)->data[0] = NULL; // erreur ici ca seg 
	return (0);
}


int loader_other(t_data **d, char *pathg, char *pathb, char *pathc, char *pathgp)
{
	int img_width;
	int img_height;
	int	i;

	i = -1;
	(*d)->grass = mlx_xpm_file_to_image((*d)->mlx, pathg, &img_width, &img_height);
	if (!(*d)->grass)
		return (1);
	(*d)->bush = mlx_xpm_file_to_image((*d)->mlx, pathb, &img_width, &img_height);
	if (!(*d)->bush)
		return (1);
	(*d)->grassp = mlx_xpm_file_to_image((*d)->mlx, pathgp, &img_width, &img_height);
	if (!(*d)->grassp)
		return (1);
	(*d)->scale = 2;
	(*d)->size = 16;
	(*d)->img = mlx_xpm_file_to_image((*d)->mlx, pathc, &img_width, &img_height);
	if (!(*d)->img)
		return (1);
	(*d)->data[0] = mlx_get_data_addr((*d)->img, &(*d)->bpp[0], &(*d)->size_line[0], &(*d)->endian[0]);
	while (++i < 6)
		crop_img(d, &(*d)->coll[i], i * 16, 0);
	mlx_destroy_image((*d)->mlx, (*d)->img);
	return (0);
}
