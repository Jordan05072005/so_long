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

char	**strrcpy(char **str)
{
	char	**cpy;
	int		i;
	int		j;

	i = -1;
	cpy = malloc((ft_strstrlen(str) + 1) * sizeof(char *));
	while (str[++i])
	{
		j = -1;
		cpy[i] = malloc((ft_strlen(str[0]) + 1) * sizeof(char));
		while (str[i][++j] != '\0')
			cpy[i][j] = str[i][j];
		cpy[i][j] = '\0';
	}
	cpy[i] = 0;
	return (cpy);
}

int	current_anim_fight(t_data *d)
{
	if (d->etat == 1 || (d->etat == 2 && d->frame != 0))
		return (1);
	return (0);
}

void	error(int coderr)
{
	ft_putstr_fd("Error\n", 1);
	if (coderr == 1)
		ft_putstr_fd("Non-compliant Map\n", 1);
	if (coderr == 2)
		ft_putstr_fd("Argument invalide or incomplet", 1);
	exit(1);
}
