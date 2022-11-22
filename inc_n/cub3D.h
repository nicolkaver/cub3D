/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:53:31 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/11/16 18:59:21 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft_n/libft.h"
# include "../gnl_n/get_next_line.h"
# include <limits.h>

# define CELL_SIZE 32
# define DIM1 1280
# define DIM2 1024
# define UP 0
# define LEFT 1
# define DOWN 2
# define RIGHT 3
# define SPEED 0.0085

typedef struct s_intPos
{
	int	x;
	int	y;
}	t_intPos;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_tex
{
	int		*ptr;
	void	*img;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	char	*path;
	int		*tab;
}			t_tex;

typedef struct s_img
{
	t_tex			*north;
	t_tex			*south;
	t_tex			*east;
	t_tex			*west;
	char			**floor_trgb;
	char			**ceiling_trgb;
	unsigned int	floor_clr;
	unsigned int	ceiling_clr;
	int				id;
}	t_img;	

typedef struct s_rc
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	ray;
	double		camx;
	t_intPos	map;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			wall_h;
	int			wall_top;
	int			wall_bot;
	double		wall_x;
	double		tex_pos;
	int			tex_x;
	int			tex_y;
}		t_rc;

typedef struct s_pic
{
	void	*image;
	char	*addr;
	int		bits_pp;
	int		line_len;
	int		endian;
}	t_pic;

typedef struct s_game
{
	char	**map;
	void	*mlx;
	void	*win;
	t_pic	pic;
	t_img	img;
	t_rc	rc;
	t_tex	*tex;
	int		up;
	int		left;
	int		down;
	int		right;
	int		rot_left;
	int		rot_right;
	int		simple_map;
	int		height;
	int		width;
	int		intro;
	char	*av;
	char	start;
}		t_game;
//int	get_color(t_tex *tex, int x, int y);
void			init_vars(t_game *game);
int				keyrelease(int key, t_game *game);
int				keypress(int key, t_game *game);
int				close_window(t_game *game);
int				render(t_game *game);
void			ray_casting(t_game *game);
void			draw_column(t_game *game, int j, t_tex *tex);
void			wall_calcs(t_rc *rc);
void			dda(t_game *game, t_rc *rc);
void			pre_dda(t_rc *rc);
void			rc_calcs(t_rc *rc, int x);
void			plane_calc(t_rc *rc, t_game *game);
void			apply_moves(t_game *game);
void			put_color(t_pic *pic, int x, int y, int color);
t_vector		rotation(t_vector vector, double angle);
t_vector		translation(t_vector pos, t_vector dir);
void			draw_background(t_game *game);
int				is_space_valid(char **trgb, int i);
//FIRST CHECKS
int				check_args(int ac, char **av);
//PARSING
int				parse(t_game *game, char *file);
int				valid_walls_2(t_game *game, char **map, int i);
int				valid_simple_map(t_game *game);
int				find_a_wall(char **map, int i, int k, int height);
int				valid_caracters(char *s, int av);
void			get_texture_path(char **tmp, t_img *img, t_game *game);
void			get_tex_path(char **tmp, t_tex *tex, t_game *game);
void			get_trgb(char **tmp, t_game *game);
unsigned int	create_rgb(int r, int g, int b);
void			my_mlx_pixel_put(t_pic *pic, int x, int y, int color);
int				get_pixel(t_tex *tex, int x, int y);
int				check_contour_t(char **map, int i);
int				real_line_is_it(t_game *game, int j);
//int				is_real_line(char *map);
//INIT
int				init_struct(t_game *game, char *file);
int				get_mapsize(t_game *game);
int				get_map(t_game *game, char *file);
void			replace_spaces_by_n(char *map);
int				init_texture_path(t_game *game, int fd, char **tmp);
void			init_malloced_img(t_game *game);
void			init_malloced_img2(t_tex *tex);
int				init_img(t_game *game);
//FREE
void			free_map(t_game *game);
void			free_mlx(t_game *game);
void			free_game(t_game *game, int loop);
void			free_and_exit(t_game *game, int exit_code);
void			free_split(char **s);
void			free_failed_img(t_game *game, int which);
void			free_img(t_game *game);
void			free_init_error(t_game *game);
void			free_malloced_img(t_tex *tex);
//RAYCASTING UTILS
void			wall_calcs(t_rc *rc);
void			get_wall_x_and_tex(t_game *game);
//int				get_color(t_tex *tex, int x, int y);
//void			draw_column(t_game *game, int j, t_tex *tex);
//void			deltadist(t_rc *rc);
//CHECK_MOVES
int				mov_up_ok(t_game *game);
int				mov_down_ok(t_game *game);
int				mov_left_ok(t_game *game);
int				mov_right_ok(t_game *game);

/*
//CHECKS
int		valid_caracters(char *s, int av); //(av = 1 check av, av = 0 chck maps)

//INIT
int		init_struct(t_game *game, char *file);
int		get_mapsize(t_game *game);
int		get_map(t_game *game, char *file);
void	init_txt(t_game *game, char *path);
t_pic	*init_picture(void);
void	init_player(t_player *player, t_game *game);
//INIT UTILS 2
int	check_xpm_format(char *str);
int	init_texture_path(t_game *game, int fd, char **tmp);

//GET COLORS
void	get_trgb(char **tmp, t_game *game);
void	get_colors(t_game *game);
void	init_ray(t_game *game);

//INIT PATH UTILS
void	get_texture_path(char **tmp, t_img **img, t_game *game);
void	get_so_path(char **tmp, t_img **img, t_game *game);
void	get_no_path(char **tmp, t_img **img, t_game *game);
void	get_ea_path(char **tmp, t_img **img, t_game *game);
void	get_we_path(char **tmp, t_img **img, t_game *game);

//PARSING
int		parse(t_game *game, char *file);
int		valid_simple_map(t_game *game);
int		valid_walls_2(t_game *game, char **map, int index);
int		find_a_wall(char **map, int i, int k, int height);

//DRAWING
void	open_map(t_game *game);
void	get_elem_txt(t_game *game);
void	ft_mlx_pixel_put(t_pic *pic, int x, int y, int color);
void	rotate_player(t_player *player);

//HOOKS
int		hook_escape(t_game *game);
int		hook_key_press(int keycode, t_game *game);
int		hook_key_release(int keycode, t_game *game);
int		hook_no_event(t_game *game);

//RENDER
void	render_game(t_game *game);
void	render_pov(t_game *game, t_pic *pic);
int		create_trgb(long int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

//DRAW 2D
void	draw_2d(t_game *game);
void	render_carre(t_game *game, t_carre carre, int color);
void    put_color(t_pic *pic, int x, int y, int color);

//TRANSLATE
void	translate(t_game *game);
void	translate_forward(t_game *game, t_player *player);
void	translate_backward(t_game *game, t_player *player);
void	translate_left(t_game *game, t_player *player);
void	translate_right(t_game *game, t_player *player);

//RAYCASTING
void	cast_rays(t_game *game, t_pic *pic);

//RAYCAST UTILS
double	get_valid_angle(double angle);
void	horizontal(t_game *game, t_ray horz, double angle, int j);
void	vertical(t_game *game, t_ray vert, double angle, int j);
int		hit_a_wall(char **map, double x, double y, t_game *game);
int		is_the_closest(double p_x, double p_y, double x_wall, double y_wall);

//RAYCAST DRAWING
void	draw_line(t_pic *pic, int j, t_game *game);
void	draw_lines(t_pic *pic, int j, t_game *game);

// UTILS
double deg2rad(double degrees);
double rad2deg(double radians);

//MOVES
void	player_movements(int keycode, t_player *player);
void	player_camera_movements(int keycode, t_player *player);
double	get_dir(double dir, int input);
int	check_player_movement(int keycode, t_game *game, t_player *player);

//FREE
void	free_map(char **map);
void	free_mlx(t_game *game);
void	free_game(t_game *game, int loop);
void	free_and_exit(t_game *game, int exit_code);
void	free_split(char **s);
void	free_failed_img(t_game *game, int which);
void	free_img(t_game *game);
void	free_init_error(t_game *game);
*/
#endif
