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
