/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:41:45 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/13 18:41:45 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	is_rectangle(char **maps)
{
	int width;
	int	i;

	width = ft_strlen(maps[0]);
	i = 1;
	while (maps[i])
	{
		if (ft_strlen(maps[i]) != width)
			return (1);
		i++;
	}
	return (0);
}

int	charfind(char **str, char find)
{
	int	i;
	int	j;
	int	counter;
	int	line;

	line = ft_strlen(str[0]) - 1;
	i = 0;
	counter = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == find)
				counter++;
			if ((i == 0 || i == ft_strlen(str[0])) && str[i][j] != '1')
				return (-1);
			if ((j == 0 || j == line) && str[i][j] != '1')
				return (-1);
			j++;
		}
		i++;
	}
	return (counter);
}

int is_possibly ()
{

}

char	**parseur(char *path)
{
	int		fd;
	char	*line;
	char	*str;
	char	**maps;

	str = NULL;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		str = ft_strjoin2(str, line);
		free(line);
		line = get_next_line(fd);
	}
	maps = ft_split(str, "\r\n");
	free(str);
	if (charfind(maps, 'E') != 1 || charfind(maps, 'C')
			< 1 || charfind(maps, 'P') != 1)
		return (NULL);
	if (is_rectangle(maps) || is_possibly())
		return (NULL);
	return (maps);
}
