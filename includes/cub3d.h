#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <string.h>
# include <stdlib.h>
# define ALIGNED 16
typedef struct	s_cub3d
{
    int			win_width;
    int			win_height;
    void		*mlx;
    void		*win;
    void		*img;
    char		*addr;
    int			bits_per_pixel;
    int			line_length;
    int			endian;
    double		posX;
    char        **map;
    double		posY;
    double		dirX;
    double		dirY;
    double		planeX;
    double		planeY;
    int			**worldMap;
} __attribute__((aligned(ALIGNED))) t_cub3d;

typedef struct  s_data
{
    int         res_x;
    int         res_y;
    char        *no_path;
    char        *so_path;
    char        *we_path;
    char        *ea_path;
    char        *s_path;
    double      deltaDistX;
    double      deltaDistY;
    double      sideDistX;
    double      sideDistY;
    double      stepX;
    double      stepY;
    int         f_color;
    int         c_color;
    char        **map;
    int         side;
    int         map_x;
    int         map_y;
    t_cub3d     *cub3d;
}__attribute__((aligned(ALIGNED))) t_data;

int     read_map(char *path, t_data *data);
void	ft_draw(t_cub3d *cub3d, t_data *data);
void    raycasting(t_cub3d *cub3d);
t_cub3d *init_cube3d(void);
t_data  *init_data(void);
void    put_map_to_window(t_cub3d *cub3d, t_data *data);

#endif
