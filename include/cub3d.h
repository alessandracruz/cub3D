/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matlopes <matlopes@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:13:42 by acastilh          #+#    #+#             */
/*   Updated: 2024/06/01 10:43:23 by matlopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 640
# define HEIGHT 480

# define MOV_SPEED 0.007
# define ROT_SPEED 0.0025

# define TEX_PATH_LEN 512
# define ERR_MLX_INIT_FAILED 1
# define ERR_WIN_CREATION_FAILED 2
# define ERR_IMG_CREATION_FAILED 3
# define ERR_MAP_PARSING_FAILED 4
# define ERROR_INVALID_FORMAT 1001
# define ERROR_CONVERSION_FAILED 1002
# define ERROR_UNKNOWN_IDENTIFIER 1003
# define ERROR_MEMORY 1004
# define ERROR_INVALID_CHAR 1005
# define ERROR_FILE_OPEN 1006
# define ERROR_READ 1007
# define ERROR_EMPTY_MAP 1008
# define ERROR_INVALID_PATH 1009
# define ERROR_MULTIPLE_PLAYERS 1010
# define ERROR_INVALID_MAP 1011
# define PARSE_OK 0

# define KEY_A 97
# define KEY_D 100
# define KEY_W 119
# define KEY_S 115
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define X 0
# define Y 1

# define NO 0
# define SO 1
# define WE 2
# define EA 3

typedef struct s_img {
	int		w;
	int		h;
	void	*ptr;
	int		*addr;
	int		bpp;
	int		size_line;
	int		endian;
	char	path[TEX_PATH_LEN];
}	t_img;

typedef struct s_map {
	int		x;
	int		y;
	int		p_check;
	t_img	tex[4];
	int		floor;
	int		ceiling;
	char	**grid;
	int		line_count;
}	t_map;

typedef struct s_lmap {
	int		x;
	int		side;
	int		map[2];
	double	pos[2];
	double	dir[2];
	int		tex[2];
	int		step[2];
	double	tex_pos;
	double	tex_step;
	int		tex_type;
	double	camera_x;
	double	plane[2];
	double	raydir[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	perp_wall_dist;
}	t_lmap;

typedef struct s_error{
	char	*message;
	int		error_code;
}	t_error;

typedef struct s_key {
	int	close;
	int	w;
	int	a;
	int	d;
	int	s;
	int	left;
	int	right;
}	t_key;

typedef struct s_data {
	void	*mlx;
	void	*win;
	char	*name;
	t_map	map;
	t_lmap	lmap;
	t_key	key;
	t_img	img;
}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_line
{
	int	start;
	int	end;
}	t_line;

/***** PARSER ******/

// COLOR_PARSER

bool	process_color_line(char *line, t_data *data, t_error *error);
int		convert_rgb_to_hex(const char *rgb);

// MAP_VALIDATE

bool	validate_map(char **map, t_error *error);

// CONFIG_PARSER

bool	process_file(FILE *file, t_error *error);
bool	process_buffer(const char *buffer, t_error *error);
bool	is_path_or_config_line(const char *line);
int		skip_to_next_line(const char *line);
bool	is_valid_character(char c);

// PLAYER_PARSER

bool	get_player_pos(t_data *data, char **map, t_error *error);

// MAP_PARSER

bool	parse_config(char *file_path, t_data *data, t_error *error);
bool	process_line(char *line, t_data *data, t_error *error, int fd);

// MAP_UTILS

int		count_map_lines(int fd);
void	free_map_grid(char ***grid, int line_count);
bool	fill_map_grid(int fd, char ***grid, int line_count, t_error *error);
bool	process_map_line(t_data *data, int fd, t_error *error);

// TEXTURE_UTILS

bool	process_texture_line(char *line, t_data *data, t_error *error);

// ARRAY_UTILS

int		ft_arraylen(char **array);
char	**ft_arraydup(char **array);
char	**add_str_in_array(char **array, char *str);
char	**fill_array_spaces(char **array);

/***** UTILS *****/

void	handle_error(int error_code, t_data *data);
bool	set_error(t_error *error, char *message, int code);
char	*ft_strldup(char *str, int size);
char	*trim_spaces(char *str);
bool	is_valid_config_line(const char *line);
bool	is_valid_map_char(char c);
bool	is_map_char(char c);
bool	is_map_line(const char *line);
void	log_message(const char *format, ...);

// DRAW

void	draw_background(t_data *data);
void	draw_ver_line(t_data *data, t_lmap *lmap, t_line line);

// LOAD_MAP

void	load_map(t_data *data);

// MOVE

int	move_ver(t_data *data, int type);
int	move_hor(t_data *data, int type);
int	rotate(t_data *data, int type);

// KEY

int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
int		key(t_data *data);

// MAIN

void	windows_builder(t_data *data);
void	clean_up(t_data *data);
int		close_hook(t_data *data);
int		main(int argc, char **argv);

#endif