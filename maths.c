#include "cube_3d.h"

// TODO Add 42 header

// Maths functions from the very useful Wolfenstein video
// Source: https://www.youtube.com/watch?v=eOCQfxRQ2pY

// delta_x - x distance from player's position to intersection point
// delta_y - same for y
// beta - the angle between player view and the horizontal
// Returns the distance from the players point of view
// NOTE This represents a correction from the obvious "distance to intersection"
// which avoids a "fisheye" distortion effect.
// TODO How does this relate to find_distance in ray.c ?
double	player_view_distance(double delta_x, double delta_y, double beta)
{
    double	pvd;

    pvd = (delta_x * cos(beta)) + (delta_y * sin(beta));
    return (pvd);
}

// Calculate beta, the player's view angle expressed as
// an angle against the horizontal.
// This is used as input to player_view_distance()
// TODO How does this vary in the non-simple cases?!
// NOTE This only needs to be calculated *once* per frame.
// TODO Could we use the wall texture derivation in this?
// theta = player's view angle, must be 0-360.
double	view_angle_horizontal(double theta)
{
    double	beta;

    if ((theta < 0) || (theta >= 360))
        return (-1);
    if (theta < 90)
    {
        // simplest case
        beta = (theta - 90);
    }
    else
        beta = 0;
    return (beta);
}

// Given a view angle (assume 90 for now) and SCREENWIDTH,
// return the number of degrees that each pixel column moves.
// This is a step needed in the loop to scan rays across the screen.
// Only needs to be calculated once per program run
// ...assuming no resizing of game window.
double	angle_per_pixel_column(void)
{
   return (90.0 / SCREENWIDTH);
}

// player_x, player_y - fractional player position coordinates
// ray_angle - where player is looking
// Returns the delta_x / stepsize to be used in casting a single ray.
// NOTE This might not be needed, done in len_find function.
double	get_delta_x(double player_x, double player_y, double ray_angle)
{
	// HACK for compilation
	(void) player_x;
	(void) player_y;
	(void) ray_angle;
    return (0.0);
}

// NOTE Assuming that x and y are valid!!
// Also starting with the assumption that we're looking at an uncomplicated angle
// I need to find the intersection coordinates
// ray_angle = bearing of the ray we are testing
// NOTE May not be needed, handled in dda_alg
void	get_wall_intersection(t_lib1 *map_data, double ray_angle)
{
    double	check_x;
    double	check_y;

    check_x = map_data->player.x;
    check_y = map_data->player.y;
	(void) check_x;
	(void) check_y;	// HACK for compilation
    ray_angle = 60.0;	// HACK for testing, remove later
	(void) ray_angle;	// HACK for compilation
}

// Convert an angle in dgress (like a compass bearing)
// to Radians (for use in making a vector)
double	degrees_to_radians(double bearing)
{
	double	rads;

	if (bearing >= 360)
		ft_printf("Warning! bearing out of range: %f", bearing);
	rads = bearing * (M_PI / 180);
	return (rads);
};

double	radians_to_degrees(double rads)
{
	double	degrees;

	if (rads > (2 * M_PI))
		ft_printf("Warning! radians out of range: %f", rads);
	degrees = rads * (180 / M_PI);
	return (degrees);
}

// Convert an angle in radians to a t_vec
t_vec	radians_to_vector(double angle)
{
	t_vec	v;

	v.x = cos(angle);
	v.y = sin(angle);
	return(v);
}
