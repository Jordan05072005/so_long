/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 04:06:37 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/13 04:06:37 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SO_LONG_H
#define _SO_LONG_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../src/get_next_line/get_next_line.h"
# include "../src/libft/libft.h"

# define display(mlx, win, img, x, y) mlx_put_image_to_window(mlx, win, img, x, y)
# define SECONDE 1000
# define wall 1
# define empty 0
# define exits 'E'
# define player 'P'
# define collectible 'C'

# define KEY_E 101 // a modif sous linux 
# define KEY_A 97 // a modif sous linux 
# define KEY_Z 122 //W
# define KEY_Q 113 //A
# define KEY_S 115 //S
# define KEY_D 100 //D
# define ESC 65307



typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**maps;
	int		lenght;
	int		height;
	void	*img;
	void	*idle[2][6];
	void	*att1[2][6];
	void	*att2[2][6];
	void	*damage[2][4];
	void	*death[2][4];
	void	*walk[2][8];
	void	*grass;
	void	*grassp;
	void	*bush;
	int		etat;
	int		frame;
	int		s_a[6];
	int		xy[2];
	int		old_xy[2];
	int		**xy_c;
	int 	hitbox;
	int 	scale;
	int 	size;
	void	*coll[6];
	char	*data[2];// Mémoire tampon de l'image
	int		bpp[2]; // Bits par pixel
	int		size_line[2];// Taille d'une ligne en octets
	int		endian[2]; // Ordre des octets
	int		type;
	int		len_key;
	struct s_data *next;
}	t_data;

//load_assets.c
int	loader_character(t_data **data, char *path, int scale, int type);
int loader_other(t_data **data, char *pathe, char *pathg, char *pathc, char *pathgp);

//MAP
//parseur.c	
char	**parseur(char *path);
//build_maps.c
int build_maps(t_data **d);

// Characters
//player_gestion.c
int	key_gestion(int keycode, t_data **data);
void	move(int keycode, t_data **d);
void	animation(t_data **d, void **img);

//Main.c
int	init(int argc, char **argv, t_data **data);
int game_loop(t_data **d);
int	close_window(t_data **d);

//UTILS
//utils.c
int	ft_strstrlen(char **str);
int	strlenchar(char **str, char find);
int	col(t_data *d, int y, int x, char obj);
int	col_hitbox(int xy1[2], int xy2[2], int s1, int s2);
int	current_anim_fight(t_data *d);

//func_lst.c
t_data *ft_newlist(char **maps);

//free.c
void	free_split(char **str);
void	free_data(t_data **d);

#endif