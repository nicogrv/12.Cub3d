/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:23:20 by ngriveau          #+#    #+#             */
/*   Updated: 2023/06/09 00:03:34 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "SuperLibft.h"
# include <math.h>
# include "../../lib/minilibx-linux/mlx.h"

# define WINX 1100
# define WINY 600
# define FOV 90
# define MINI_MAP_COLOR_WALL 0x990000
# define MINI_MAP_COLOR_VOID 0xffffff
# define MINI_MAP_COLOR_PLAYER 0xffff00

// # define TOUCH_LEFTARROW 65361
// # define TOUCH_RIGHTARROW 65363
// # define TOUCH_UPARROW 65362
// # define TOUCH_DOWNARROW 65364
// # define TOUCH_MOINS 45
// # define TOUCH_PLUS 61
// # define TOUCH_ONE 49
// # define TOUCH_TOW 50
// # define TOUCH_THREE 51
// # define TOUCH_FOUR 52
// # define TOUCH_FIVE 53
// # define TOUCH_W 119
// # define TOUCH_A 97
// # define TOUCH_S 115
// # define TOUCH_D 100
// # define ESC 65307
// # define TOUCH_C 99
// # define TOUCH_X 120
// # define TOUCH_M 109
// # define TOUCH_N 110
// # define TOUCH_I 105
// # define TOUCH_P 112

# define TOUCH_LEFTARROW 123
# define TOUCH_RIGHTARROW 124
# define TOUCH_UPARROW 126
# define TOUCH_DOWNARROW 125
# define TOUCH_MOINS 27
# define TOUCH_PLUS 24
# define TOUCH_ONE 18
# define TOUCH_TOW 19
# define TOUCH_THREE 20
# define TOUCH_W 13
# define TOUCH_A 0
# define TOUCH_S 1
# define TOUCH_D 2
# define ESC 53
# define TOUCH_C 8
# define TOUCH_X 7
# define TOUCH_M 46
# define TOUCH_N 45
# define TOUCH_I 34
# define TOUCH_P 35
# define TOUCH_FOUR 21
# define TOUCH_FIVE 230


# define RAD 57.295779513

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	color;
	int	id;
}				t_color;

typedef struct s_raycast
{
	float	cosx;
	float	cosy;
	float	tanx;
	float	tany;
}				t_raycast;

typedef struct s_img
{
	int		size;
	int		p;
	int		e;
	char	*data;
	int		r;
	int		b;
	int		g;
}	t_img;

typedef struct s_texture
{
	void	*i;
	void	*tex;
	char	*path;
	int		width;
	int		height;
	t_img	img;
}				t_texture;

typedef struct s_mlx
{
	int		winx;
	int		winy;
	void	*mlx;
	void	*mlx_win;
	void	*i;
	int		size;
	int		p;
	int		e;
	char	*data;
	int		r;
	int		g;
	int		b;

}				t_mlx;

typedef struct s_data
{
	t_mlx		mlx;
	int			**map;
	int			fdfile;
	char		*pathfile;
	t_texture	north;
	t_texture	mini;
	t_texture	east;
	t_texture	south;
	t_texture	west;
	t_raycast	trigo;
	t_color		sky;
	t_color		floor;
	int			mapx;
	int			mapy;
	float		playerx;
	float		playery;
	float		playerr;
	int			playerfov;
	int			lenwall;
	int			ystartmap;
	int			x;
	int			y;
	int			nbrpl;
	float		i;
	float		ax;
	float		hyv;
	float		hyr;
	float		posx;
	float		posy;
	float		decalx;
	float		decaly;
	float		length;
	int			face;
	int			pcofwall;
	float		nbr_column;

}	t_data;

void	ft_ray_270_360(t_data *d);
void	ft_ray_180_270(t_data *d);
void	ft_ray_90_180(t_data *d);
void	ft_ray_0_90_pt2(t_data *d);
void	ft_ray_0_90(t_data *d);

int		ft_init_id_verif_color(t_color *color, int *id, char *line, int i);
int		ft_init_id_verif_color_pt2(int i, int *id, char *line, int *j);
int		ft_init_id_verif_color_pt3(char *tmp, int *j, char *line, t_color *c);
void	ft_init_id_verif_color_pt4(char *tmp, t_color *color);

int		ft_init_id(t_data *data, char **returnline);
int		ft_init_id_pt2(char *li, int i, int id);
int		ft_init_id_pt3(t_data *data, char *li, int *id, int i);
int		ft_init_id_pt4(t_data *data, char *li, int *id, int i);
int		ft_init_id_pt5(t_data *data, int id);
void	ft_init_id_pt6(t_data *data, char **li, char **returnline);
int		ft_check_name_file(char *str);

int		ft_map(t_data *data);
int		ft_map_pt2(t_data *data, int *y, int x, int fd);
void	ft_map_pt3(t_data *data, int y, int x, char *line);
void	ft_size_map(t_data *data, char *line);

int		ft_ray(t_data *data);
void	ft_ray_pt2(t_data *data);
int		ft_ray_pt3(t_data *data);
void	ft_ray_pt4(t_data *data);

int		ft_key(int keycode, t_data *data);
void	ft_key_2(int keycode, t_data *data);
void	ft_key_3(int keycode, t_data *data);
void	ft_key_4(int keycode, t_data *data);

//Free
int		ft_free_mlx(t_data *data);
void	ft_free_path_tex(t_data *data);
void	ft_free_map(t_data *data, int y);

void	ft_draw(t_data *data, float x, float y, int color);
void	ft_draw_mini(t_data *data, float x, float y, int color);
int		ft_pixel_of_img(t_data *data, int face, int pcofwall, int y);
void	ft_pixel_of_img_2(t_data *data, int face, int pcofwall, int y);

int		ft_verif_ok_map(t_data *data);
void	ft_verif_ok_map_pt2(t_data *data);
void	ft_verif_ok_map_pt3(t_data *data);

int		ft_init(int c, char **av, t_data *data);
void	ft_init_2(t_data *data);
void	ft_initmlx(t_data *data);
void	ft_init_minimap(t_data *data);
int		ft_init_id_verif_path(char **path_for_data, int *id, char *line, int i);

void	ft_color(int nbr, t_data *data);
void	ft_color_colone(t_data *data, int x, float len, int pcofwall);

int		ft_mouse_move(t_data *data);
int		ft_cross_close(t_data *data);

int		is_ws(char c);
int		is_player(int c);
int		ft_is_wc_or_new_line(char *line);

int		main(int c, char **av);

# define NC "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define ORANGE "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define LIGHTGRAY "\033[0;37m"

# define DARKGRAY "\033[1;30m"
# define LIGHTRED "\033[1;31m"
# define LIGHTGREEN "\033[1;32m"
# define LIGHTBLUE "\033[1;34m"
# define LIGHTPURPLE "\033[1;35m"
# define LIGHTCYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"

#endif