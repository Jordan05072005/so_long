/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:49:24 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/07 15:49:24 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	crop_img2(t_data **d, int scale, char *src, int *v)
{
	unsigned int	color;
	char			*dest;

	while (++v[2] < scale)
	{
		v[3] = -1;
		while (++v[3] < scale)
		{
			dest = (*d)->data[1] + ((v[1] * scale + v[2])
					* (*d)->size_line[1] + (v[0] * scale + v[3])
					* ((*d)->bpp[1] / 8));
			color = *(unsigned int *)src;
			if ((color & 0xFF000000) == 0x00000000)
				*(unsigned int *)dest = color;
		}
	}
}

void	crop_img(t_data **d, void **img, int x_start, int y_start)
{
	int		v[4];
	char	*src;
	int		size;
	int		scale;

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
