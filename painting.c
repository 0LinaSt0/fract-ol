/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:11:06 by msalena           #+#    #+#             */
/*   Updated: 2021/10/02 17:26:22 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/* Do algorithm of suming z^2 and c */
double	sum_z_and_c_steps(t_data *img, int x_pixel, int y_pixel, int *n)
{
	double		z_modul;
	t_z_pl_c	z_c;

	z_modul = 0.0;
	if (img->type_fl == 'm')
		initial_of_z_sqre (img->first_input, img->second_input, &z_c, img);
	else if (img->type_fl == 'j')
		initial_of_z_sqre (x_pixel, y_pixel, &z_c, img);
	while (*n < 30 && (z_modul < 2.0))
	{
		if (*n > 1)
			z_sqre (&z_c);
		if (img->type_fl == 'm')
			z_sqre_plus_c (x_pixel, y_pixel, &z_c, img);
		else if (img->type_fl == 'j')
			z_sqre_plus_c (img->first_input, img->second_input, &z_c, img);
		z_modul = take_module(&z_c);
		(*n)++;
	}
	return (z_modul);
}

void	fractol_painting(t_color *color, t_data *img)
{
	if (color->z_modul > 2.0)
		*((int *)(img->addr + color->y_pixel * img->line_length
					+ color->x_pixel * (img->bits_per_pixel / 8)))
			= create_color (1, 127 + color->n * color->n, 255
				+ color->n * 2, 212 + color->n);
	else
		*((int *)(img->addr + color->y_pixel * img->line_length
					+ color->x_pixel * (img->bits_per_pixel / 8)))
			= create_color (1, 0, 0, 0);
}

/* Iterated over pixels in open window*/
void	iterate_in_window(t_data *img, int x_input, int y_input)
{
	t_color	color;

	color.n = 1;
	color.x_pixel = 0;
	color.y_pixel = 0;
	color.z_modul = 0.0;
	img->first_input = x_input;
	img->second_input = y_input;
	while (color.y_pixel < D_WIDTH)
	{
		while (color.x_pixel < D_WIDTH)
		{
			color.z_modul = sum_z_and_c_steps(img, color.x_pixel,
					color.y_pixel, &color.n);
			fractol_painting(&color, img);
			color.n = 1;
			color.x_pixel++;
		}
		color.x_pixel = 0;
		color.y_pixel++;
	}
	mlx_put_image_to_window (img->mlx, img->wind, img->img, 0, 0);
}
