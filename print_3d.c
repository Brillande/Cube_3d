#include "cube_3d.h"

// NOTE Is this is a general function we could use elsewhere?
//Esta función obtiene el valor RGBA de un píxel en una textura dada

static int	get_rgba(mlx_texture_t *texture, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;
    // extrae los valores de los colores de la textura
	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
    // Combina los componentes en un solo valor entero RGBA
	return (r << 24 | g << 16 | b << 8 | a);
}

// TODO Give this function a useful name and description
// esta función llena la estructura info con la información necesaria para dibujar una pared
void fill_info(t_info *info, t_lib1 *data, double height) {
    // asigna la textura correspondiente a la pared
    info->tex = data->texture[data->player.side];
    // calcula los valores de top, bottom y text_start
    if (height >= SCREENHEIGHT) {
        info->top = 0;
        info->bottom = SCREENHEIGHT - 1;
        info->text_start = (((1 - (1.0 * SCREENHEIGHT / height)) / 2.0)
                            * info->tex->height);
    } else {
        info->top = (SCREENHEIGHT - height) / 2;
        info->bottom = (SCREENHEIGHT + height) / 2;
        info->text_start = 0.0;
    }
    // calcula el paso de la textura en función de la altura de la pared
    info->step = 1.0 * info->tex->height / height;
}

// TODO Work out how this relates to the get_background function
//esta función dibuja el techo y el suelo
void draw_ceiling_and_floor(t_lib1 *data, int i) {
    int start = 0;
    int half = (SCREENHEIGHT - start) / 2;

    // Dibuja el techo
    while (start < half) {
        mlx_put_pixel(data->img, i, start, data->rgb_ceiling);
        start++;
    }
    // Dibuja el suelo
    while (start < SCREENHEIGHT) {
		// FIXME invalid write here
        mlx_put_pixel(data->img, i, start, data->rgb_floor);
        start++;
    }
}

// FIXME The EAST and NORTH values here will need to be changed, post-enumeration
// What was specific about those two that meant the maths would be different?
// NOTE What does player.side represent?
// NOTE What does player.ray represent?
// NOTE What is t_info doing?
// Esta función dibuja las paredes en la pantalla
void walls(t_lib1 *data, int i)
{
    double height;
    int x;
    t_info info;
    // Calcula la altura de la pared en la pantalla
    height = SCREENHEIGHT / data->player.ray;
    x = 0;
     // Llena la estructura info con los datos necesarios para dibujar la pared
    fill_info(&info, data, height);
    // Dibuja el techo y el suelo
    draw_ceiling_and_floor(data, i);
     // Dibuja la pared píxel por píxel
    while (x < info.bottom - info.top) {
        if (data->player.side == EAST || data->player.side == NORTH)
            info.color = get_rgba(info.tex,
                                  ((unsigned int)((1.0 - data->player.wall_x)
                                                  * info.tex->width)),
                                  ((unsigned int)(info.text_start + x * info.step)));
        else
            info.color = get_rgba(info.tex,
                                  ((unsigned int)((data->player.wall_x) * info.tex->width)),
                                  ((unsigned int)(info.text_start + x * info.step)));
        // Coloca el píxel en la imagen
        mlx_put_pixel(data->img, i, x + info.top, info.color);
        x++;
    }
    i++;
}
