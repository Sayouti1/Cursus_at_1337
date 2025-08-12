/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-sayo <aes-sayo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:23:06 by aes-sayo          #+#    #+#             */
/*   Updated: 2024/02/06 17:23:11 by aes-sayo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img
{
	int		width;
	int		height;
	void	*c_img;
	void	*p_front_img;
	void	*p_back_img;
	void	*p_img;
	void	*w_img;
	void	*f_img;
	void	*e_img;
	void	*e_close_img;
	void	*e_open_img;
	void	*n_img;
}			t_img;

typedef struct s_map
{
	t_img	imgs;
	int		width;
	int		height;
	int		c;
	int		e;
	int		p;
}			t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	int		win_x;
	int		win_y;
	int		moves;
	char	**map;
	t_map	map_s;
}			t_vars;

/*_____________________________main.c_______________________________________*/
void		display_moves(t_vars *vars);
void		load_images(t_vars *vars);
void		load_images_compl(t_vars *vars);
void		start_map(t_vars *vars);

/*_____________________________check_functions.c____________________________*/
void		flood_fill_collectible(t_vars *vars, char **copy_map, int x, int y);
int			flood_fill_exit(t_vars vars, char **copy_map, int x, int y);
int			check_map(t_vars *vars);
int			check_textures(t_vars *vars);

/*_____________________________free_functions.c__________________________*/
void		free_vars(t_vars *vars);
void		*free_arr(char **arr);
void		free_and_exit(t_vars *vars);
int			close_x(t_vars *vars);
void		print_error(char *str, int end);

/*_____________________________map_functions.c______________________________*/
int			ft_strlen_gnl(char *str);
char		*ft_strjoin_lines(char *old_line, char *buff);
char		*read_file(int fd);
char		**get_map(char *path);
int			init_map(t_vars *vars);

/*_____________________________map_utils.c__________________________________*/
int			get_player_x(t_vars vars);
int			get_player_y(t_vars vars);
int			get_map_height(char **map);
char		**get_copy_map(t_vars vars);
void		display_image_at(t_vars *vars, int i, int j);

/*_____________________________moves_functions.c____________________________*/
void		move_top(t_vars *vars, int x, int y);
void		move_right(t_vars *vars, int x, int y);
void		move_down(t_vars *vars, int x, int y);
void		move_left(t_vars *vars, int x, int y);
int			ft_input(int key, t_vars *vars);

/*_____________________________so_long_utils.c______________________________*/
void		init_vars(t_vars *vars);
int			enemy_exists(char **map);
int			valid_map(char *str);

/*_____________________________validation_functions.c_______________________*/
int			is_valid_ext(char *path);
int			is_rectangular(t_vars vars);
int			is_surrounded(t_vars vars);
int			is_valid_path_to_exit(t_vars *vars);

#endif
