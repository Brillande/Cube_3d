/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedina- <emedina-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:47:24 by emedina-          #+#    #+#             */
/*   Updated: 2025/02/26 18:57:43 by emedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d.h"

// Convert an angle in degrees (like a compass bearing)
// to Radians (for use in making a vector)
// TODO Consider if further correction is needed, considering S in the map has
// y increasing...where would this matter?
// NOTE Some sources say that a heading vector converts in the range -PI to +PI
// (A circle has 2 PI radians)
double	degrees_to_radians(double bearing)
{
	double	rads;

	if ((bearing >= 360) || (bearing < 0))
		ft_printf("Warning! bearing out of range: %f", bearing);
	rads = bearing * (M_PI / 180);
//	rads -= M_PI;	// HACK Correction to place us in the +/- PI range
	return (rads);
}

// NOTE This is unused and could be removed
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
	return (v);
}

// Transform vector coords x & y by rotating per angle
void	rotate_vector(double *x, double *y, double rads)
{
	double	temp_x;

	temp_x = *x;
	*x = *x * cos(rads) - *y * sin(rads);
	*y = temp_x * sin(rads) + *y * cos(rads);
}
