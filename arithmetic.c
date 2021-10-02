/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:11:12 by msalena           #+#    #+#             */
/*   Updated: 2021/10/02 17:11:14 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Initializes struct in first time for pixel => squaring Z^2
	Formula ---------->    z^2 = (x + yi)^2 = (x^2 - y^2) + (2 * x * y) */
void	initial_of_z_sqre(int x, int y, t_z_pl_c *z, t_data *img)
{
	double	x_new;
	double	y_new;

	if (img->type_fl == 'j' && (img->zoom_fl == 4 || img->zoom_fl == 5))
	{
		x_new = (-2 + (double)J_WIDTH / (double)D_WIDTH * x)
			/ img->zoom_fl_count;
		y_new = (-2 + (double)J_WIDTH / (double)D_WIDTH * y)
			/ img->zoom_fl_count;
	}
	else
	{
		x_new = (-2 + (double)J_WIDTH / (double)D_WIDTH * x);
		y_new = (-2 + (double)J_WIDTH / (double)D_WIDTH * y);
	}
	z->valid_z = (pow(x_new, 2) - pow(y_new, 2));
	z->imaginary_z = (2.0 * x_new * y_new);
}

/* Squaring z Formula ---------->
	z^2 = (change_x^2 - change_y^2) + (2 * change_x * change_y) */
void	z_sqre(t_z_pl_c *z)
{
	double	came_imaginary;

	came_imaginary = z->imaginary_z;
	z->imaginary_z = (2 * z->valid_z * came_imaginary);
	z->valid_z = (pow(z->valid_z, 2) - pow(came_imaginary, 2));
}

/* Addition two complex numbers
	Formula ---------->
	z = (z + c) = (change_x^2 - change_y^2 + x_outpute)
							+ (2*change_x*change_y + y_outpute) */
void	z_sqre_plus_c(double x, double y, t_z_pl_c *z_c, t_data *img)
{
	double		x_new;
	double		y_new;

	if (img->type_fl == 'm' && (img->zoom_fl == 4 || img->zoom_fl == 5))
	{
		x_new = (-2 + (double)J_WIDTH / (double)D_WIDTH * x)
			/ img->zoom_fl_count;
		y_new = (-2 + (double)J_WIDTH / (double)D_WIDTH * y)
			/ img->zoom_fl_count;
	}
	else
	{
		x_new = (-2 + (double)J_WIDTH / (double)D_WIDTH * x);
		y_new = (-2 + (double)J_WIDTH / (double)D_WIDTH * y);
	}
	z_c->valid_z = (z_c->valid_z + x_new);
	z_c->imaginary_z = (z_c->imaginary_z + y_new);
}

/* Take module of tne z (which result or addition z and c already).
   Formula ----------->    sqrt(z) = sqrt(x^2 + y^2)  */
double	take_module(t_z_pl_c *z_c)
{
	return (sqrt((pow(z_c->valid_z, 2)) + (pow(z_c->imaginary_z, 2))));
}
