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

// TODO Ensure all these includes are permitted
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
# define FIELDOFVIEW 60	// TODO Consider removing this, or define as radians not degrees not properly used.

// NOTE This is of use for texture arrays but *not* player.side!
enum e_direction
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

// Will things be more clear passing around a struct for the vectors?
// Player orientation, each ray, camera plane...?
typedef struct s_vec
{
	double	x;
	double	y;
} t_vec;

// This holds *only* things to do with the player and their view (ie camera plane)
typedef struct s_player
{
    double pa; // Ángulo de orientación del jugador IN DEGREES
    double x; // CARTESIAN Coordenada x del jugador
    double y; // CARTESIAN Coordenada y del jugador
	// NOTE I think ray and wall_x are more accurately properties of a RAY not the player.
    double ray; // Longitud del rayo Length of ray from (player or camera plane) to wall.
    double wall_x; // Coordenada x de la pared	NOTE porque no hay wall_y?? Scanning?
    int side; // Lado del impacto	NOTE Should this then be e_direction?
//	t_vec	camera;	// vector of the camera plane
	double x_camera; // VECTOR Coordenada x de la cámara plane
    double y_camera; // VECTOR Coordenada y de la cámara
    double game_speed; // Velocidad del juego
} t_player;

// Badly-named sruct to hold info for texture drawing (?)
typedef struct s_info {
    mlx_texture_t *tex;
    double top;
    double bottom;
    double text_start;
    double step;
    int color;
} t_info;

// What do we *actually need* in these things? So much duplication!
typedef struct	s_ray
{
    double ray_x; // Coordenada x del rayo - must be a VECTOR
    double ray_y; // Coordenada y del rayo - must be a VECTOR
    int map_x; // Coordenada x del mapa POR EL RAY
    int map_y; // Coordenada y del mapa POR EL RAY
    int	direction_x; // +/- 1 for the x direction of a ray
    int	direction_y; // +/- 1 for the y direction of a ray
    double		side_dist_x; // Length of ray from current position to next x-side
    double		side_dist_y; // Length of ray from current position to next y-side
    double delta_x; // Delta x - length of ray from one x side to next x-side
    double delta_y; // Delta y - length of ray from one x side to next x-side
	int	axis;	// Either north-south or east-west. Determines calculation type.
	double	length;	// the key result! How far has our ray travelled before striking a wall?
	double	wall_strike;	// AKA wall_x, the point on the wall struck by the ray
}	t_ray;

// Definición de la estructura t_lib1
// TODO Review data in struct, remove not-needed elements (e.g. number of coins)
// TODO Consider separating game state from image / window data
// ...another sensible split could be things that change on movement v things that don't?
// TODO How do we change "number of columns" - the map is not a rectangle.
typedef struct s_lib1 {
    t_player player;
    int		hit;	// Indicador de impacto de un rayo con el pared
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
	// NOTE This below should / could be turned into a vector?
	int		player_faces;		// The direction the player is facing at the start. IN DEGREES
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
} t_lib1;

int		main(int argc, char **argv);
void		init_game(t_lib1 *map_data);
void		open_window(t_lib1 *map_data);
int		print_img(t_lib1 *map_data);
void		move(t_lib1 *data);
/* void		key_left(t_lib1 *data); */
/* void		key_right(t_lib1 *data); */
void		key_d(t_lib1 *data);
void		key_a(t_lib1 *data);
void		key_s(t_lib1 *data);
void		key_w(t_lib1 *data);
// moves
void	rotate_left(t_player *p);
void	rotate_right(t_player *p);

void		key_hook(mlx_key_data_t keydata, void *info);
int		exit_game(t_lib1 *map_data);
void		draw_3d(t_lib1 *data);
void		walls(t_lib1 *data, int i);
int		check_move(int x, int y, t_lib1 *data);
double		len_find(t_lib1 *data, double angle);
void		dda_alg(t_lib1 *data);
//void		get_step_and_side(t_lib1 *cal);	// formerly find_ray
void	get_step_and_side(t_ray *data, t_player player);

void	dda_for_one_ray(t_ray *ray, char **map_array);
//t_ray	setup_ray(t_lib1 *data, double rads);
t_ray	setup_ray(t_lib1 *data, double rads, double camera_x);
double	find_distance_ray(t_ray *ray);
// Display things on the windows
mlx_image_t	*make_background(t_lib1 *map_data);
void	solid_walls(t_lib1 *data, double distance, int screen_col, mlx_image_t *img);
//void	find_strike_point(t_ray *r, double x_origin, double y_origin);
double	find_strike_point(t_ray *r, double x_origin, double y_origin);

// Debugging files
void	print_read_from_file(t_lib1 map_data);
void	print_map_array(t_lib1 *map_data);
void	print_start_position(t_lib1 *map_data);
void	print_ray_properties(t_ray ray);
void	print_player_info(t_player p);

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
void		setup_player(t_lib1 *map_data);
void		setup_camera_plane(double rads, t_player *player);

// file_helpers.c
char		*find_next_line(int fd);
int		test_path(char *path);
char		*check_extension(char *map_extension);
void		join_the_fullpath(t_lib1 *map_data, char *map_name);
int		line_is_blank(char *line);

// maths functions
double	player_view_distance(double delta_x, double delta_y, double beta);
double	angle_per_pixel_column(void);
double	view_angle_horizontal(double theta);
double	degrees_to_radians(double bearing);
t_vec	radians_to_vector(double angle);
double	radians_to_degrees(double rads);
double	get_camera_x(int screen_col);
void	rotate_vector(double *x, double *y, double rads);

// exit routines
void	clear_data(t_lib1 *map_data);

void player (void * param);
int	create_trgb(int t, int r, int g, int b);
#endif
