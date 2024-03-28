/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastilh <acastilh@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:13:42 by acastilh          #+#    #+#             */
/*   Updated: 2024/03/27 23:50:19 by acastilh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define NAME "cub3D"
# define WIDTH 1280
# define HEIGHT 720
# define FLOOR '0'
# define WALL '1'
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

#define TEX_PATH_LEN 512

typedef struct s_texture
{
    char north[TEX_PATH_LEN]; // Caminho para a textura do norte
    char south[TEX_PATH_LEN]; // Caminho para a textura do sul
    char west[TEX_PATH_LEN];  // Caminho para a textura do oeste
    char east[TEX_PATH_LEN];  // Caminho para a textura do leste
} 	t_texture;

typedef struct s_color
{
    int floor;   // Cor do chão em formato hexadecimal 0xRRGGBB
    int ceiling; // Cor do teto em formato hexadecimal 0xRRGGBB
}	t_color;

typedef struct s_map
{
    char **grid;  // Matriz de caracteres representando o mapa
    int width;    // Largura do mapa
    int height;   // Altura do mapa
}	t_map;

typedef struct s_player
{
    double x;       // Posição X do jogador no mapa
    double y;       // Posição Y do jogador no mapa
    double dir_x;   // Direção X da visão do jogador
    double dir_y;   // Direção Y da visão do jogador
}	t_player;

typedef enum e_parse_error {
    PARSE_OK = 0, // Nenhum erro
    ERROR_TEXTURE,
    ERROR_COLOR,
    ERROR_MAP
}	t_parse_error;

typedef struct s_config
{
    t_texture textures; // Estrutura para as texturas
    t_color colors;     // Estrutura para as cores
    t_map map;          // Estrutura para o mapa
    t_player player;    // Estrutura para o jogador
	t_parse_error parse_error;  // Estrutura de tratamento de erros geral
}	t_config;

/****** PARSER ******/

// MAP_CONFIG_PARSER

int		read_map_config(char *file_path, t_config *config);

// PARSE_LINE

bool	parse_texture_line(char *line, t_texture *textures);
bool	parse_color_line(char *line, t_color *colors);
bool	parse_map_line(char *line, t_map *map);
void	parse_line(char *line, t_config *config);

/****** UTILS ******/

char *get_next_line_trim(char *line);

#endif

/*
// Estrutura para representar o mapa
typedef struct s_map
{
	char	**array;
	int		width;
	int		height;
}	t_map;

// Incluído no arquivo cub3d.h

typedef struct s_img
{
	int		height;
	int		width;
	void    *img_ptr;      // Ponteiro para a imagem da textura
	char    *addr;         // Endereço do pixel da imagem
	int     bits_per_pixel; // Quantidade de bits por pixel
	int     line_length;    // Comprimento de linha da imagem
	int     endian;         // Formato endian da imagem
}	t_img;

typedef struct s_texture
{
	t_img   *north; // Textura do lado norte
	t_img   *south; // Textura do lado sul
	t_img   *east;  // Textura do lado leste
	t_img   *west;  // Textura do lado oeste
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_player
{
    double posX, posY;  // Posição do jogador
    double dirX, dirY;  // Direção do jogador
    double planeX, planeY; // Plano da câmera do jogador, para cálculo de FOV
    double moveSpeed;   // Velocidade de movimento
    double rotSpeed;    // Velocidade de rotação
}   t_player;

typedef struct s_game
{
    void        *mlx;       // Ponteiro para a instância MLX
    void        *win;       // Ponteiro para a janela
    t_map       map;        // Mapa do jogo
    t_texture   textures;   // Texturas do jogo
    t_player    player;     // Jogador
}   t_game;


// Declarações de funções

void		init_player(t_player *player);

// Função para carregar o mapa

// MAIN
int		main(int argc, char **argv);

***** PARSE_MAPS *****

// COLORS.C

int			check_rgb_range(int r, int g, int b);
int			convert_rgb_to_int(char **rgb_components);
void		ft_free_str_array(char **array);
char		*trim_line(int fd);
int			parse_floor_ceiling_color(char *line, int *color, char identifier);

// MAP_CONFIG

void		parse_map_config(t_game *game, char *config_path);
void		parse_map_config(t_game *game, char *config_path)

// MAP_KEYS.C

int		is_valid_key(char *key);
int		is_duplicate_key(char *key, t_game *game);

// MAP_SIZE.C

void calculate_map_size(t_map *map, const char *map_file_path);

// MAP_PARSER.C

void	load_texture(t_game *game, char *direction, char *path);

// TEXTURE_MANAGEMENT.C

void validate_and_load_texture(t_game *game, const char *line);

// TEXTURE_UTILS.C

int		validate_and_load_data(void *mlx_ptr, char *texture_path,
		t_img **target_texture);

***** START *****

void	load_textures_and_colors(t_game *game);
void	init_cub(t_game *game);
void	render_map(t_game *game);
*/

