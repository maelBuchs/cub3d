/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:18:44 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/13 14:04:10 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define DR 0.0174533
# define FOV 60.0f


typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
} __attribute__((aligned(ALIGNED))) t_img;

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
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*s_path;
	t_img	*no_img;
	t_img	*so_img;
	t_img	*we_img;
	t_img	*ea_img;
	int		f_color;
	int		c_color;
} __attribute__((aligned(ALIGNED))) t_cub3d;

typedef struct s_data
{
	int		res_x;
	int		res_y;
	float	stepx;
	float	stepy;
	int		charac;
	int		*map_x;
	int		*map_y;
	char	**map;
	int		side;
	int		map_width;
	int		map_height;
	int		left;
	int		right;
	int		up;
	int		down;
	int		turn_left;
	int		turn_right;
	int		minimap;
	t_cub3d	*cub3d;
} __attribute__((aligned(ALIGNED))) t_data;

typedef struct s_ray
{
	int				lineheight;
	int				mapx;
	int				mapy;
	float			raydirx;
	float			raydiry;
	float			sidedistx;
	float			sidedisty;
	float			deltadistx;
	float			deltadisty;
	int				drawstart;
	int				drawend;
	int				stepx;
	int				stepy;
	float			dirx;
	float			diry;
	int				side;
	int				x;
	float			distance;
	unsigned int	color;
} __attribute__((aligned(ALIGNED))) t_ray;

char		**read_map(char *path, t_data *data);
void draw_minimap_ray(t_data *data);
void		ft_draw(t_cub3d *cub3d, t_data *data);
t_cub3d		*init_cube3d(void);
t_data		*init_data(void);
void		draw_pixel(t_cub3d *cub3d, int x, int y, int color);
int			ft_exit(t_data *data, char *str);
void		set_player(t_cub3d *cub3d, t_data *data);
int			update(t_data *data);
int init_textures(t_data *data);
void		init_mlx(t_data *data, t_cub3d *cub3d);
void		grrr(t_data *data);
void		draw_rays(t_data *data);
float		trace_ray(t_data *data, float angle);
void		draw_fat_pixel(t_cub3d *cub3d, int x, int y, int color);
int ft_tablen(char **tab);
void		draw_vertical_line(t_cub3d *cub3d, int x, t_ray *ray);
void		render_scene(t_data *data);
void		grrr(t_data *data);
void		clear_screen(t_cub3d *cub3d);
void		initializeray(t_data *data, float angle, t_ray *ray);
void		rotate(t_data *d, double angle);
void		move_side(t_data *d, int dir);
void		player_move(t_data *d, int dir);
int	press_key(int keycode, void *data);
int is_map_closed(t_data *data);
int get_longest_line(char **map);
int	unpress_key(int keycode, void *data);
#endif
