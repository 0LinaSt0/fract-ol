/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:10:58 by msalena           #+#    #+#             */
/*   Updated: 2021/10/02 17:10:59 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* Zoom fractol */
void	zoom(int key_code, int *x, int *y, t_data *img)
{
	if (img->input_fl == 'y')
	{
		*x = img->first_input;
		*y = img->second_input;
	}
	if (key_code == 4)
	{
		img->zoom_fl = 4;
		img->zoom_fl_count *= 0.5;
	}
	else
	{
		img->zoom_fl = 5;
		img->zoom_fl_count /= 0.5;
	}
}

/* Handles of mouse signals */
int	mouse_pos(int key_code, int x, int y, t_data *img)
{
	static int	x_old_j = 375;
	static int	x_old_m = 750;
	static int	y_old = 750;

	if (key_code == 4 || key_code == 5)
	{
		if (img->type_fl == 'm')
		{
			zoom(key_code, &x_old_m, &y_old, img);
			iterate_in_window(img, x_old_m, y_old);
		}
		else if (img->type_fl == 'j')
		{
			zoom(key_code, &x_old_j, &y_old, img);
			iterate_in_window(img, x_old_j, y_old);
		}
	}
	else
	{
		iterate_in_window(img, x, y);
		y_old = y;
		x_old_m = x;
		x_old_j = x;
	}
	return (0);
}

/* Close windows after pressing ESC */
int	close(int key_code, t_data *img)
{
	printf ("key = %d\n", key_code);
	if (key_code == 53)
	{
		mlx_destroy_image(img->mlx, img->img);
		mlx_destroy_window(img->mlx, img->wind);
		exit(0);
	}
	return (1);
}

/* Gives arguments for creating new fractol with gived parametres*/
void	give_arguments_for_creating(int argc, char **argv, t_data *img)
{
	img->first_input = 0;
	img->second_input = 0;
	img->input_fl = 'n';
	if (argc == 2)
	{
		if (img->type_fl == 'm')
			iterate_in_window(img, D_WIDTH / 2, D_WIDTH / 2);
		else if (img->type_fl == 'j')
			iterate_in_window(img, D_WIDTH / 4, D_WIDTH / 2);
	}
	else
	{
		img->input_fl = 'y';
		img->first_input = modern_atoi(argv[2]);
		img->second_input = modern_atoi(argv[3]);
		iterate_in_window(img, img->first_input, img->second_input);
	}
}

int	main(int argc, char **argv)
{
	t_data	img;

	img.type_fl = 0;
	img.zoom_fl_count = 1;
	if (argc < 2)
		invalid_messag(1);
	check_arguments_on_disability(argc, argv, &img);
	img.mlx = mlx_init();
	img.img = mlx_new_image(img.mlx, D_WIDTH, D_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.wind = mlx_new_window(img.mlx, D_WIDTH, D_WIDTH, "prived_medved");
	give_arguments_for_creating(argc, argv, &img);
	mlx_mouse_hook (img.wind, mouse_pos, &img);
	mlx_key_hook(img.wind, close, &img);
	mlx_loop(img.mlx);
}
