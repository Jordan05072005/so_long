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
	int	j;

	i = -1;
	while ((*d)->xy_c[++i])
		free((*d)->xy_c[i]);
	free((*d)->xy_c);
	i = -1;
	free_img(d, (*d)->idle[0], (*d)->s_a[0]);
	free_img(d, (*d)->att1[0], (*d)->s_a[1]);
	free_img(d, (*d)->att2[0], (*d)->s_a[2]);
	free_img(d, (*d)->damage[0], (*d)->s_a[3]);
	free_img(d, (*d)->death[0], (*d)->s_a[4]);
	free_img(d, (*d)->walk[0], (*d)->s_a[5]);
	mlx_destroy_image((*d)->mlx, (*d)->grass);
	mlx_destroy_image((*d)->mlx, (*d)->grassp);
	mlx_destroy_image((*d)->mlx, (*d)->bush);
	free_img(d, (*d)->coll, 6);
	//mlx_destroy_image((*d)->mlx, (*d)->img);
	free_split((*d)->maps);
	// mlx_destroy_image((*d)->mlx, img);
}
