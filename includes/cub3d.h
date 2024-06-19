/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:18:44 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/19 22:52:45 by mbuchs           ###   ########.fr       */
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
# define DR 0.0174533
# define FOV 60.0f



typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	int		*txt;
}	t_img;

typedef struct s_texture
{
	int		*no_txt;
	int		*so_txt;
	int		*we_txt;
	int		*ea_txt;
	t_img	*img_struct;
	int		x;
	int		y;
}	t_texture;

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
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*s_path;
	t_img	*no_img;
	t_img	*so_img;
	t_img	*we_img;
	t_img	*ea_img;
	t_img	*actual_texture;
	int		f_color;
	int		c_color;
	int 	tex_x;
}	t_cub3d;

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
}	t_data;

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
}	t_ray;

/*
* Initialisation functions
*/
t_cub3d		*init_cube3d(void);
t_data		*init_data(void);
t_ray		*init_ray(void);
void		init_mlx(t_data *data, t_cub3d *cub3d);
void		init_texture(t_texture *texture);
t_img		*init_img(void);
/* 
* Parsing functions and utils
*/
int			ft_tablen(char **tab);
int			ft_exit(t_data *data, char *str);
char		*ft_strndup(char *src, int n);
int			is_map_closed(t_data *data);
int			get_longest_line(char **map);
char		**read_map(char *path, t_data *data);
void	free_tab(void **tab);	
void		set_player(t_cub3d *cub3d, t_data *data);
/* 
* Fast math functions
*/
float		fast_cos(float angle);
float		fast_sin(float angle);
/*
* Texture functions
*/
int			init_textures(t_data *data, t_cub3d *cub3d);
t_img		*check_texture(t_ray *ray, t_cub3d *cub3d);
void		draw_texture(t_cub3d *cub3d, t_ray *ray, t_img *img);
int			compute_wall_texture(t_img *img, t_ray *ray, t_data *data);
void		load_texture(t_img *img, int **texture);
/*
* Key Hooks functions
*/
void		rotate(t_data *d, double angle);
void		move_side(t_data *d, int dir);
void		player_move(t_data *d, int dir);
int			press_key(int keycode, void *data);
int			unpress_key(int keycode, void *data);
void		move(t_data *d, t_ray *ray, float posx, float posy);
/*
* Raycasting functions
*/
void		ft_draw(t_cub3d *cub3d, t_data *data);
void		draw_pixel(t_cub3d *cub3d, int x, int y, int color);
int			update(t_data *data);
void		draw_rays(t_data *data);
float		trace_ray(t_data *data, float angle);
void		draw_fat_pixel(t_cub3d *cub3d, int x, int y, int color);
void		draw_vertical_line(t_cub3d *cub3d, int x, t_ray *ray);
void		render_scene(t_data *data, t_cub3d *cub3d);
void		grrr(t_data *data, t_cub3d *cub3d);
void		clear_screen(t_cub3d *cub3d);
void		set_ray(t_cub3d *cub3d, float angle, t_ray *ray, t_data *data);
int			dda(t_data *data, t_ray *ray);
float		calculate_distance(t_ray *ray, t_data *data);
char **update_map(t_data *data, int mode);

#endif