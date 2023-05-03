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






typedef struct s_color 
{
	int r;
	int	g;
	int	b;
	int color;
}				t_color;


typedef struct s_data 
{
	int		**map;
	int		fdfile;
	char	*pathfile;
    char	*pathnorth;
    char	*pathsouth;
    char	*pathwest;
    char	*patheast;
	t_color	sky;
	t_color	floor;
	int		mapy;
	int		mapx;
	int		ystartmap;

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