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

#define SCREENWIDTH 640
#define SCREENHEIGHT 480
#define EAST 2
#define WEST 3
#define NORTH 4
#define SOUTH 
#define TRUE 1
#define FALSE 0

typedef struct s_player {
    double pa; // Ángulo de orientación del jugador
    double x; // Coordenada x del jugador
    double y; // Coordenada y del jugador
    double ray; // Longitud del rayo
    double wall_x; // Coordenada x de la pared
    int side; // Lado del impacto
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
typedef struct s_lib1 {
    t_player player;
    char **map;
    int hit; // Indicador de impacto
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
    int rgb_ceiling; // Color del techo
    int rgb_floor; // Color del suelo
    void *texture[4];
	int len_cols; // Número de columnas
    int len_rows; // Número de filas
	mlx_t *mlx;
	char	**map_array;
	char	**cpy_of_map_array;
	int		player_coor_x;
	int		player_coor_y;
	int		how_many_lines;
	int		how_many_colums;
	int		map_length;
	int		x;
	int		y;
	int		count;
	char	*fullpath;
	char	*map_content;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
	void	*win;
	int		width;
	int		heigth;
	void	*ground;
	void	*coin;
	void	*exit;
	void	*wall;
	int		end;
	int		coins_collected;
	int		total_coins;
	int		cpy_coors_x;
	int		cpy_coors_y;
} t_lib1;
int			main(int argc, char **argv);
void		isnt_borded_of_walls(char **map_array, int lines, int colms);
int			hasnt_forbidden_char(char *map_content);
char		*check_name(char *map_name);
char		*check_extension(char *map_extension);
t_lib1		*join_the_fullpath(t_lib1 *map_data, char *map_name);
t_lib1		*read_the_map(t_lib1 *map_data);
char		*read_map(char *full_path, int i);
int			how_length_is_the_map(char *full_path);
t_lib1		*test_to_knows_if_is_playable(t_lib1 *map_data);
int			count_words(const char *str, char c);
void		so_many_p_e_c_has(t_lib1 *map_data, char **map);
t_lib1		*test_to_knows_if_is_playable2(t_lib1 *map_data);
int			count_p_e_c(char **map, t_lib1 *map_data, char target);
void		flood_fill(t_lib1 *map_data, int x, int y);
void		find_out_if_is_playable(t_lib1 *map_data);
t_lib1		*init_game(t_lib1 *map_data);
void		open_window(t_lib1 *map_data);
void		select_img(t_lib1 *map_data);
int			print_img(t_lib1 *map_data);
void		move(t_lib1 *data);
void		key_left(t_lib1 *data);
void		key_right(t_lib1 *data);
void		key_d(t_lib1 *data);
void		key_a(t_lib1 *data);
void		key_s(t_lib1 *data);
void		key_w(t_lib1 *data);
void		key_hook(mlx_key_data_t keydata, void *info);
int			exit_game(t_lib1 *map_data);
void		print_img2(t_lib1 *map_data);
int			st_map(char x, int i);
int			st_temp(char c, int i);
void		print_img3(t_lib1 *map_data);
void		print_img1(t_lib1 *map_data);
void		flood_fill1(t_lib1 *map_data, int x, int y);
void		find_out_if_is_playable2(t_lib1 *map_data, int playable);
void		print_3d(t_lib1 *data);
void		walls(t_lib1 *data, int i);
int			check_move(int x, int y, t_lib1 *data);
double		len_find(t_lib1 *data, double angle);
void	dda_alg(t_lib1 *data, t_lib1 *ca);
void	find_ray(t_lib1 *cal, t_lib1 *data);

#endif