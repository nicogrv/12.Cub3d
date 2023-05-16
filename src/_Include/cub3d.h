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



# define WINX 2500
# define WINY 1400
# define FOV 90

#  define TOUCH_LEFTARROW 65361
#  define TOUCH_RIGHTARROW 65363
#  define TOUCH_UPARROW 65362
#  define TOUCH_DOWNARROW 65364
#  define TOUCH_MOINS 45
#  define TOUCH_PLUS 61
#  define TOUCH_ONE 49
#  define TOUCH_TOW 50
#  define TOUCH_THREE 51
#  define TOUCH_FOUR 52
#  define TOUCH_FIVE 53
#  define TOUCH_W 119
#  define TOUCH_A 97
#  define TOUCH_S 115
#  define TOUCH_D 100
#  define ESC 65307
#  define TOUCH_C 99
#  define TOUCH_X 120
#  define TOUCH_M 109
#  define TOUCH_N 110
#  define TOUCH_I 105
#  define TOUCH_P 112

// #  define TOUCH_LEFTARROW 123
// #  define TOUCH_RIGHTARROW 124
// #  define TOUCH_UPARROW 126
// #  define TOUCH_DOWNARROW 125
// #  define TOUCH_MOINS 27
// #  define TOUCH_PLUS 24
// #  define TOUCH_ONE 18
// #  define TOUCH_TOW 19
// #  define TOUCH_THREE 20
// #  define TOUCH_W 13
// #  define TOUCH_A 0
// #  define TOUCH_S 1
// #  define TOUCH_D 2
// #  define ESC 53
// #  define TOUCH_C 8
// #  define TOUCH_X 7
// #  define TOUCH_M 46
// #  define TOUCH_N 45
// #  define TOUCH_I 34
// #  define TOUCH_P 35
// #  define TOUCH_FOUR 21
// #  define TOUCH_FIVE 230
#  define RAD 57.295779513

typedef struct s_color 
{
	int r;
	int	g;
	int	b;
	int color;
}				t_color;

typedef struct s_mouse
{
	int b;
}				t_mouse;

typedef struct s_raycast
{
	float cosx;
	float cosy;
	float tanx;
	float tany;
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
	t_mouse		mouse;
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
	int 		lenwall;
	int			ystartmap;

} 				t_data;







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