/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:23:09 by emedina-          #+#    #+#             */
/*   Updated: 2024/11/30 15:56:40 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H
# include "./libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdint.h>

# define SCREENWIDTH 640
# define SCREENHEIGHT 480

enum e_direction
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

typedef struct s_player {
    double pa; // Ángulo de orientación del jugador
    double x; // Coordenada x del jugador
    double y; // Coordenada y del jugador
    double ray; // Longitud del rayo
    double wall_x; // Coordenada x de la pared
    int side; // Lado del impacto	NOTE Should this then be e_direction?
	double x_camera; // Coordenada x de la cámara
    double y_camera; // Coordenada y de la cámara
    double game_speed; // Velocidad del juego
} t_player;

typedef struct s_info {
    mlx_texture_t *tex;
    double top;
    double bottom;
    double text_start;
    double step;
    int color;
} t_info;

// Definición de la estructura t_lib1
// TODO Review data in struct, remove not-needed elements (e.g. number of coins)
// TODO Consider separating game state from image / window data
// TODO How do we change "number of columns" - the map is not a rectangle.
typedef struct s_lib1 {
    t_player player;
    char **map;		// NOTE What is the difference between this and map_content?
    int hit; // Indicador de impacto entre rayo y pared
    double side_x; // Lado x
    double side_y; // Lado y
    double delta_x; // Delta x
    double delta_y; // Delta y
    int map_x; // Coordenada x del mapa
    int map_y; // Coordenada y del mapa
    int step_x; // Paso x
    int step_y; // Paso y
    double ray_x; // Coordenada x del rayo
    double ray_y; // Coordenada y del rayo
    void *img; // Imagen
    int	rgb_ceiling; // Color del techo
    int	rgb_floor; // Color del suelo
    void 	*texture[4];		// NOTE The N, S, E, W images loaded from...
	char	*texture_paths[4];	// NOTE New, perhaps temporary
	int len_cols; // Número de columnas NOTE sería el maximo
    int len_rows; // Número de filas NOTE sería el maximo
	mlx_t *mlx;
	char	**map_array;
	int		player_coor_x;		// Player starting position, x coord
	int		player_coor_y;		// Player starting position, y coord
	int		player_faces;		// The direction the player is facing at the start.
	int		how_many_lines;		// TODO Differences between these, len_cols, width?
	int		how_many_colums;
	int		map_length;		// NOTE IS this needed?
	int		x;
	int		y;
	int		count;			// NOTE count of what??
	int 	wind;
	char	*fullpath;
	char	*map_content;	// NOTE I assume this is the "raw" map data and map above is it as a structured array?
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;			// NOTE what colour is this? Obsolete with rgb_* ?
	void	*win;			// TODO How does this work? We are not setting it now.
	int		width;
	int		heigth;
	void	*wallE;
	void	*wallN;
	void	*wallS;
	void	*wallW;
	int		end;	// TODO Check to see if this should be removed
} t_lib1;

int		main(int argc, char **argv);
t_lib1		*init_game(t_lib1 *map_data);
void		open_window(t_lib1 *map_data);
int		print_img(t_lib1 *map_data);
void		move(t_lib1 *data);
void		key_left(t_lib1 *data);
void		key_right(t_lib1 *data);
void		key_d(t_lib1 *data);
void		key_a(t_lib1 *data);
void		key_s(t_lib1 *data);
void		key_w(t_lib1 *data);
void		draw_3d(t_lib1 *data);
void		key_hook(mlx_key_data_t keydata, void *info);
int		exit_game(t_lib1 *map_data);
void		draw_3d(t_lib1 *data);
void		walls(t_lib1 *data, int i);
int		check_move(int x, int y, t_lib1 *data);
double		len_find(t_lib1 *data, double angle);
void		dda_alg(t_lib1 *data);
void		find_ray(t_lib1 *cal);

// Display things on the windows
mlx_image_t	*make_background(t_lib1 *map_data);

// Debugging files
void	print_read_from_file(t_lib1 map_data);
void	print_map_array(t_lib1 *map_data);
void	print_start_position(t_lib1 *map_data);

// Parsing the files
void		read_map_from_fd(t_lib1 *map_data, int fd);
void		get_visuals(t_lib1 *map_data, int fd);
int		get_orientation(char c);
void		map_is_playable(t_lib1 *map_data);
int		only_legal_char(char *map_content);
char		*check_name(char *map_name);
int		check_each_square(t_lib1 *map_data);
int		only_one_player(char *map);
void		get_start_position(t_lib1 *map_data);
void		load_wall_textures(t_lib1 *map_data);

// file_helpers.c
char		*find_next_line(int fd);
int		test_path(char *path);
char		*check_extension(char *map_extension);
void		join_the_fullpath(t_lib1 *map_data, char *map_name);
int		line_is_blank(char *line);

// exit routines
void	clear_data(t_lib1 *map_data);

void player (void * param);
int	create_trgb(int t, int r, int g, int b);
#endif