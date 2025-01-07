/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 22:14:54 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/13 22:14:54 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_img(t_data **d, void **img, int frame)
{
	int	i;

	i = -1;
	while (++i < frame)
		mlx_destroy_image((*d)->mlx, img[i]);
}

void	free_data(t_data **d)
{
	int	i;

	i = -1;
	while ((*d)->xy_c[++i])
		free((*d)->xy_c[i]);
	free((*d)->xy_c);
	i = -1;
	free_img(d, (*d)->idle, (*d)->s_a[0]);
	free_img(d, (*d)->att1, (*d)->s_a[1]);
	free_img(d, (*d)->att2, (*d)->s_a[2]);
	free_img(d, (*d)->damage, (*d)->s_a[3]);
	free_img(d, (*d)->death, (*d)->s_a[4]);
	free_img(d, (*d)->walk, (*d)->s_a[5]);
	free_img(d, (*d)->exit, 7);
	mlx_destroy_image((*d)->mlx, (*d)->grass);
	mlx_destroy_image((*d)->mlx, (*d)->grassp);
	mlx_destroy_image((*d)->mlx, (*d)->bush);
	mlx_destroy_image((*d)->mlx, (*d)->coll);
	free_split((*d)->maps);
}
