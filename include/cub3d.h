/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:13:42 by acastilh          #+#    #+#             */
/*   Updated: 2024/04/17 18:55:09 by acastilh         ###   ########.fr       */
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

# define TEX_PATH_LEN 512
# define WIDTH 640
# define HEIGHT 480
#define ERR_MLX_INIT_FAILED 1
#define ERR_WIN_CREATION_FAILED 2
#define ERR_IMG_CREATION_FAILED 3
#define ERR_MAP_PARSING_FAILED 4
// Adicione mais conforme necessário

typedef struct s_map {
    char north[TEX_PATH_LEN]; // Caminho para a textura do norte
    char south[TEX_PATH_LEN]; // Caminho para a textura do sul
    char west[TEX_PATH_LEN];  // Caminho para a textura do oeste
    char east[TEX_PATH_LEN];  // Caminho para a textura do leste
    int floor;   // Cor do chão em formato hexadecimal 0xRRGGBB
    int ceiling; // Cor do teto em formato hexadecimal 0xRRGGBB
    char **grid; // Matriz de caracteres representando o mapa
    int line_count; // Contagem de linhas do mapa
} t_map;

typedef struct s_data {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    char *name;
    t_map map; // Adicionado aqui
} t_data;

/***** PARSER ******/

// COLOR_UTILS

bool	process_color_line(char *line, t_data *data);
int		convert_rgb_to_hex(const char *rgb);

// MAP_PARSER

void	start(t_data *data);
bool	parse_config_file(char *file_path, t_data *data);

// MAP_UTILS

int		count_map_lines(const char *file_path);
void	free_map_grid(char ***grid, int line_count);
bool	fill_map_grid(int fd, char ***grid, int line_count);
bool	process_map(t_data *data, const char *file_path);

// TEXTURE_UTILS

bool	process_texture_line(char *line, t_data *data);

/***** UTILS *****/

void	handle_error(int error_code, t_data *data);
char	*trim_spaces(char *str);
bool	is_valid_config_line(const char *line);
bool	is_valid_map_char(char c);
bool	is_map_char(char c);
bool	is_map_line(const char *line);
void	log_message(const char *format, ...);


// MAIN

void	windows_builder(t_data *data);
void	clean_up(t_data *data);
int		close_hook(t_data *data);
int		main(int argc, char **argv);

#endif


/*
# define NAME "cub3D"
# define WIDTH 1280
# define HEIGHT 720
# define FLOOR '0'
# define WALL '1'
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define TEX_PATH_LEN 512
# define BUFFER_SIZE 32

typedef struct s_texture
{
	char north[TEX_PATH_LEN]; // Caminho para a textura do norte
	char south[TEX_PATH_LEN]; // Caminho para a textura do sul
	char west[TEX_PATH_LEN];  // Caminho para a textura do oeste
	char east[TEX_PATH_LEN];  // Caminho para a textura do leste
}			t_texture;

typedef struct s_color
{
	int floor;   // Cor do chão em formato hexadecimal 0xRRGGBB
	int ceiling; // Cor do teto em formato hexadecimal 0xRRGGBB
}			t_color;

typedef struct s_map
{
	char **grid; // Matriz de caracteres representando o mapa
	int width;   // Largura do mapa
	int height;  // Altura do mapa
}			t_map;

typedef struct s_player
{
	double x;     // Posição X do jogador no mapa
	double y;     // Posição Y do jogador no mapa
	double dir_x; // Direção X da visão do jogador
	double dir_y; // Direção Y da visão do jogador
}			t_player;

typedef enum e_parse_error
{
	PARSE_OK = 0, // Nenhum erro
	ERROR_TEXTURE,
	ERROR_COLOR,
	ERROR_MAP,
	ERROR_MEMORY,
	ERROR_INVALID_CHAR,
    ERROR_MISSING_PLAYER,
    ERROR_OPEN_WALL,
    ERROR_MULTIPLE_PLAYERS,
	ERROR_MAP_EMPTY,
}		t_parse_error;


typedef struct s_config
{
	t_texture textures;        // Estrutura para as texturas
	t_color colors;            // Estrutura para as cores
	t_map map;                 // Estrutura para o mapa
	t_player player;           // Estrutura para o jogador
	t_parse_error parse_error; // Estrutura de tratamento de erros geral
	bool is_map_start; 		   // Flag para indicar o início do processamento do mapa
	bool textures_loaded;      // Indica se todas as texturas foram carregadas
    bool colors_loaded;        // Indica se as cores foram definidas
	bool configurations_processed;
}			t_config;

****** PARSER ******

// MAP_CONFIG_PARSER

int			read_map_config(char *file_path, t_config *config);
void		print_parse_error(t_parse_error error_code, char *line);

// PARSE_LINE

bool		parse_texture_line(char *line, t_texture *textures);
bool		parse_color_line(char *line, t_color *colors);
bool		parse_map_line(char *line, t_map *map, t_config *config);
void		parse_line(char *line, t_config *config);
void		update_loaded_flags(t_config *config);
void		process_configuration_line(char *trimmed_line, t_config *config);

// VALIDATE_MAP

bool		validate_map(t_map *map, t_config *config);
bool		validate_map_chars(t_map *map, t_config *config);
bool		validate_player_start(t_map *map, t_config *config);
bool		validate_walls_closed(t_map *map, t_config *config);

****** GAME ******

// INITIALIZATION

void		initialize_player_direction(t_player *player, char orientation);
void		set_player_position(t_config *config, int x, int y, char orientation);

****** UTILS ******

// GET_NEXT_LINE_TRIM

char		*get_next_line_trim(char *line);

// COLOR_UTILS

bool		check_colors_loaded(t_color *colors);
bool		validate_color(int color);

// TEXTURE_UTILS

bool		check_textures_loaded(t_texture *textures);
bool		validate_texture(char *path);

#endif
*/
