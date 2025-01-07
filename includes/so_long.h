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
# define SECONDE 500
# define wall '1'
# define empty '0'
# define exits 'E'
# define player 'P'
# define collectible 'C'
# define mob 'M'

# define KEY_E 101 // a modif sous linux 
# define KEY_A 97 // a modif sous linux 
# define KEY_Z 122 //W
# define KEY_Q 113 //A
# define KEY_S 115 //S
# define KEY_D 100 //D
# define ESC 65307

# define SX_EXIT 24 
# define SY_EXIT 14
# define HX_EXIT 13
# define HY_EXIT 42
# define HX_COLL 16
# define HX_PLAYER 20
# define SX_P 40
# define SY_P 37


typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**maps;
	int		lenght;
	int		height;
	void	*img;
	void	*idle[6];
	void	*att1[6];
	void	*att2[6];
	void	*damage[4];
	void	*death[4];
	void	*walk[8];
	void	*grass;
	void	*grassp;
	void	*bush;
	void	*exit[7];
	int		etat;
	int		frame;
	int		frame2;
	int		s_a[6];
	int		xy[2];
	int		old_xy[2];
	int		**xy_c;
	int		xy_exit[2];
	int		s_x[2];
	int 	scale;
	int 	size;
	void	*coll;
	char	*data[2];// Mémoire tampon de l'image
	int		bpp[2]; // Bits par pixel
	int		size_line[2];// Taille d'une ligne en octets
	int		endian[2]; // Ordre des octets
	int		type;
	int		keys_pressed;
	int		level;
}	t_data;

//load_assets.c
int	loader_character(t_data **data, char *path, int scale, int type);
int loader_other(t_data **data);
//loader_utils.c
void	crop_img(t_data **d, void **img, int x_start, int y_start);
void	crop_img2(t_data **d, int scale, char *src, int *v);

//MAP
//parseur.c	
char	**parseur(char *path);
//build_maps.c
int build_maps(t_data **d);
int *find_coo(t_data **d, char find);
//event.c
void	level(t_data **d);
void	animation(t_data **d, void **img);
void	animation_static(t_data **d, void **img, int size, int xy[2]);
void	del_coll(t_data **d);

// Characters
//characters_gestion.c
void	move(int keycode, t_data **d);
int	key_gestion(int keycode, t_data **data);

//Main.c
int	init(char **argv, t_data **data);
int game_loop(t_data **d);
int	close_window(t_data **d);

//UTILS
//utils.c
int	ft_strstrlen(char **str);
int	strlenchar(char **str, char find);
int	current_anim_fight(t_data *d);
char	**strrcpy(char **str);
void	error(int coderr);
//utils2.c
void	fill_co(int co[2], int x, int y);

//collison.c
int	col(t_data **d, int y, int x, char obj);
int	col_player_coins(t_data **d, int s1, int s2, int s3);
int	col_player_elem(t_data **d, int *xy , int x2, int y2);

//func_lst.c
t_data *ft_newlist(char **maps);

//free.c
void	free_split(char **str);
void	free_data(t_data **d);

#endif