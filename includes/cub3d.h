#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define ALIGNED 16
# define FOV 60.0f

typedef struct s_cub3d
{
	int		win_width;
	int		win_height;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
	float	posx;
	float	posy;
	float	dirx;
	float	diry;
	float	planex;
	float	planey;
	int		**worldMap;
} __attribute__((aligned(ALIGNED))) t_cub3d;

typedef struct s_data
{
	int		res_x;
	int		res_y;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*s_path;
	float	deltaDistx;
	float	deltaDisty;
	float	sideDistx;
	float	sideDisty;
	float	stepx;
	float	stepy;
	int		charac;
	int		f_color;
	int		c_color;
	char	**map;
	int		side;
	int		map_x;
	int		map_y;
	int		map_width;
	int		map_height;
	int		left;
	int		right;
	int		up;
	int		down;
	int		minimap;
	t_cub3d	*cub3d;
} __attribute__((aligned(ALIGNED))) t_data;
int is_map_closed(t_data *data);

char		**read_map(char *path, t_data *data);
void		ft_draw(t_cub3d *cub3d, t_data *data);
void		raycasting(t_cub3d *cub3d);
t_cub3d		*init_cube3d(void);
t_data		*init_data(void);
void		put_map_to_window(t_cub3d *cub3d, t_data *data);
void		plot_map(t_data *data);
void		draw_pixel(t_cub3d *cub3d, int x, int y, int color);
int			ft_exit(t_data *data, char *str);
void		parse_map(char *path, t_data *data);
void        set_player(t_cub3d *cub3d, t_data *data);
int         update(t_data *data);
void        init_mlx(t_data *data, t_cub3d *cub3d);

#endif
