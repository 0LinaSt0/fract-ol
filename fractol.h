/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:11:16 by msalena           #+#    #+#             */
/*   Updated: 2021/10/02 17:11:16 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define D_WIDTH 800
# define J_WIDTH 4

# include "minilibx_opengl_20191021/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	void	*img;
	void	*wind;
	void	*mlx;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		zoom_fl;
	double	zoom_fl_count;
	char	type_fl;
	int		first_input;
	int		second_input;
	char	input_fl;
}			t_data;

typedef struct s_z_pl_c
{
	double	valid_z;
	double	imaginary_z;
}			t_z_pl_c;

typedef struct s_color
{
	int			n;
	int			x_pixel;
	int			y_pixel;
	double		z_modul;
}				t_color;

void	initial_of_z_sqre(int x, int y, t_z_pl_c *z, t_data *img);
void	z_sqre(t_z_pl_c *z);
void	z_sqre_plus_c(double x, double y, t_z_pl_c *z_c, t_data *img);
double	take_module(t_z_pl_c *z_c);

int		create_color(int t, int r, int g, int b);
double	sum_z_and_c_steps(t_data *img, int x_pixel, int y_pixel, int *n);
void	fractol_painting(t_color *color, t_data *img);
void	iterate_in_window(t_data *img, int x_input, int y_input);

char	julia_or_mandelbrot(char *str, char **argv);
void	invalid_messag(int fl);
void	check_arguments_on_disability(int argc, char **argv, t_data *img);
int		modern_atoi(const char *nptr);
char	check_on_invalid_nums(char *argv);

#endif
