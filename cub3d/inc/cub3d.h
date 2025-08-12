/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarda <hbarda@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-06 16:42:21 by hbarda            #+#    #+#             */
/*   Updated: 2025-01-06 16:42:21 by hbarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define NUM_TEXTURES 4
# define NUM_COLORS 2

# define NO 0
# define SO 1
# define WE 2
# define EA 3

# define SUPPORTED_CHARS "NSEW01\t\n "
# define PLAYER_DIR "NSEW"

# ifndef PI
#  define PI 3.14159265358
# endif

typedef struct s_img
{
	void		*img;
	void		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			w;
	int			h;

}				t_img;

typedef struct s_textures
{
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
	int			floor_color;
	int			ceil_color;
}				t_textures;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;

	int			player_dir;

	double		angle;
	double		fov;
	int			move_forward;
	int			move_right;
	int			turn_right;
	double		move_speed;
	double		turn_speed;
}				t_player;

typedef struct s_ray
{
	double		ray_angle;
	int			is_facing_up;
	int			is_facing_right;
	double		hit_x;
	double		hit_y;
	double		wall_h;
	double		r_wall_h;
	double		distance;
	double		top_y;
	double		bottom_y;
	double		r_top_y;
	double		r_bottom_y;
	int			hit_vertical;
}				t_ray;

typedef struct s_intersection
{
	double		distance;
	double		x;
	double		y;
}				t_intersection;

typedef struct s_step
{
	double		x;
	double		y;
}				t_step;

typedef struct s_map
{
	int			*map_line_len;
	int			map_start;
	int			fd;
	char		**map;
	int			height;
	int			width;
	int			redraw;

}				t_map;

typedef struct s_screen
{
	double		width;
	double		height;
	double		obj_size;
}				t_screen;

typedef struct s_data
{
	void		*ptr;
	void		*win;
	char		**lines;
	int			textures_found;
	int			colors_found;
	char		*textures_path[NUM_TEXTURES];
	char		*trimmed;
	t_img		img;
	t_img		*texture[NUM_TEXTURES];
	t_screen	screen;
	t_map		map;
	t_textures	textures;
	t_player	player;
	t_ray		*rays;

}				t_data;

/*-------------------------AES_SAYO_[START]-----------------*/
char			**split_on_two(char *line, char *del);
/*collision.c*/
int				inter_check(t_data *data, int idx, double *inter,
					int is_horizon);
t_intersection	get_horizontal_intersection(t_data *data, int i);
t_intersection	get_vertical_intersection(t_data *data, int i);

/*drawing.c*/
int				draw_square_at(t_data *data, double x, double y, int col);
int				draw_ray(t_data *data, int x);
int				draw_map(t_data *data);
int				draw_aim_cross(t_data *data);

/*exit.c*/
int				ft_close(t_data *data);
int				free_textures(t_data *data);

/*getters.c*/
double			get_distance_between(double x1, double y1, double x2,
					double y2);
int				get_color(t_data *data, int i);
t_img			*get_img(t_data *data, int i);
char			**get_map(t_data *param);

/*image_utils.c*/
int				put_color_to_pixel(t_data *data, int x, int y, int col);
int				put_pixel_to_pixel(t_data *data, t_img *img, int x, int y);

/*initializer.c*/
int				init_cub(t_data *data);

/*key_handling.c*/
int				valid_key(int key, t_data *data);
int				ft_key_press(int key, t_data *data);
int				ft_key_release(int key, t_data *data);

/*map_utils.c*/
char			*ft_strjoin_gnl(char *old_line, char *new_line);
int				pixel_inside_map(t_data *data, double x, double y);
int				pixel_in_screen(t_data *data, double x, double y);
int				player_inside_map(t_data *data, double player_x,
					double player_y);
int				pixel_inside_map(t_data *data, double x, double y);

/*player_movement.c*/
int				move_forward_backward(t_data *data, double *new_x,
					double *new_y);
int				move_right_left(t_data *data, double *new_x, double *new_y);
double			turn_right_left(t_data *data, int turn_right);

/*rendering.c*/
int				render_map(t_data *data, int s, int e);
int				render_rays(t_data *data);
int				render_player(t_data *data);

/*setters.c*/
int				set_ray_data(t_data *data, int i);
void			set_offset_x_y(t_data *data, int *offset_x, int *offset_y);

/*update.c*/
int				update_map(t_data *data);
int				update_player(t_data *data);

/*utils.c*/
// int                 ft_strlen(char *s);
double			normalize_angle(double angle_tofix);

/*-------------------------AES_SAYO_[END]--------------------*/

/*------------------------HBARDA_[START]--------------------*/

int				ft_isspace(char c);
int				arr_len(char **array);

int				parse_map(t_data *data, int ac, char **av);

int				check_extension(const char *file_path, const char *extension);

int				is_empty_line(const char *line);
int				is_empty_map(const char *map_path, int *height);
char			**read_lines(int fd, int *height);
char			**read_map_lines(const char *map_path, int *height);

int				validate_map_cont(t_data *data, char **lines, int height);

int				parse_metadata(t_data *data, char **map_lines, int map_heigh,
					int *current_line);

void			free_parse_allocated(t_data *data, char **parts, char *message);
void			free_array(char **arr);
void			ft_free_all(char *msg, t_data *data, int exit_status);

int				get_texture_pos(char *texture_dir);
void			validate_texture(t_data *data, char **parts,
					int *textures_found);

void			ft_free_all(char *msg, t_data *data, int exit_status);
void			free_all(t_data *data);

void			validate_color(t_data *data, char **parts, int *current_line,
					int *colors_found);
int				check_color_format(char *str_color);
int				parse_color(char *str_color);

char			**copy_array(char **array, int array_len);

void			init_map(t_data *data, char **lines, int current_line,
					int height);

int				validate_map(t_data *data);
void			check_map_characters(t_data *data, int i, int j,
					int *is_player_found);

int				validate_map_borders(t_data *data, char **map, int height);
int				check_first_last(t_data *data, char **map, int height);
int				check_left_right(t_data *data, char **map, int height);
void			check_map_lr(t_data *data, int height, int i, int j);

int				**init_int_arr(int *lines_len, int arr_len);
void			free_int_array(int **int_array, int arr_len);

void			fill_empty_spaces(t_data *data);
int				is_valid_cell_surroundings(t_data *data, int i, int j);

int				process_metadata_lines(t_data *data, char **map_lines,
					int map_height, int *current_line);
int				parse_metadata_line(t_data *data, char *line,
					int *current_line);
int				is_start_of_map(char *line);
int				validate_identifier(t_data *data, char **parts,
					int *current_line);
void			check_args_num(t_data *data, char **parts, int *current_line);
int				get_color_parsed(char **colors);
int				split_len(char **str);

int				is_valide_color(char *col);

char			*clean_color_str(char *str);
/*---------------------------HBARDA_[START]--------------------*/
#endif