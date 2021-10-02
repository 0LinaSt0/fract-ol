/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalena <msalena@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:11:02 by msalena           #+#    #+#             */
/*   Updated: 2021/10/02 17:11:02 by msalena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	modern_atoi(const char *nptr)
{
	size_t		i;
	long int	n;
	size_t		z;

	i = 0;
	n = 0;
	z = 1;
	while (nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			z = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = n * 10 + (nptr[i] - '0');
		i++;
	}
	n *= z;
	if (n < 0 || n > 1500)
		invalid_messag(0);
	return (n);
}

void	invalid_messag(int fl)
{
	printf ("\n     !!!invalid arguments!!!\n\n");
	if (fl == 1)
	{
		printf (" Please, enter one of this command:\n");
		printf ("	mandelbrot\n");
		printf ("	julia\n\n");
	}
	else
		printf ("Please, enter two numbers: from 0 to 1500\n\n");
	exit (0);
}

/* Check arguments on quantity and correctiness */
void	check_arguments_on_disability(int argc, char **argv, t_data *img)
{
	char	ret_j;
	char	ret_m;

	ret_j = julia_or_mandelbrot("julia\0", argv);
	ret_m = julia_or_mandelbrot("mandelbrot\0", argv);
	if (ret_j == 'n' && ret_m == 'n')
		invalid_messag(1);
	else if (ret_j == 'y' && ret_m == 'n')
		img->type_fl = 'j';
	else if (ret_j == 'n' && ret_m == 'y')
		img->type_fl = 'm';
	if (argc == 3)
		invalid_messag(0);
	if (argc > 3 && (check_on_invalid_nums(argv[2]) == 'n'
			|| check_on_invalid_nums(argv[3]) == 'n'))
	{
		invalid_messag(0);
	}
}

/*Check arguments for correctiness: it should be just numbers
	from 0 to 1500*/
char	check_on_invalid_nums(char *argv)
{
	int		i;
	char	fl;

	i = 0;
	fl = 't';
	while (argv[i])
	{
		if (argv[i] != '0' && argv[i] != '1' && argv[i] != '2'
			&& argv[i] != '3' && argv[i] != '4' && argv[i] != '5'
			&& argv[i] != '6' && argv[i] != '7' && argv[i] != '8'
			&& argv[i] != '9')
		{
			fl = 'f';
		}
		i++;
	}
	if (fl == 'f')
		return ('n');
	else
		return ('y');
}

/*Check which str (mandelbrot or julia) came from input*/
char	julia_or_mandelbrot(char *str, char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i] == str[i] && argv[1][i] && str[i])
		i++;
	if (!argv[1][i] && !str[i])
		return ('y');
	else
		return ('n');
}
