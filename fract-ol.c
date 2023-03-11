/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract-ol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romaurel <romaurel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:59:02 by romaurel          #+#    #+#             */
/*   Updated: 2023/03/10 19:47:45 by romaurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract-ol.h"

void	putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(1, &s[i++], 1);
}

char	*tolow(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	return (s);
}

void	fractal_island(char c, t_prog *prog)
{
	if (c == 'j')
		julia(prog, prog->win);
	if (c == 'm')
		mandelbrot(prog, prog->win);
	if (c == 'b')
		burningship(prog, prog->win);
}

void	p_start(char set, double re, double im)
{
	t_prog	prog;

	// Dimension window
	prog.pos.w = 700;
	prog.pos.h = 540;

	// woom
	prog.pos.zoom = 1;
	prog.pos.moveX = 0;
	prog.pos.moveY = 0;
	prog.f.set = set;
	prog.f.color = 0x0009EE10;

	// julia
	prog.f.cRe = re;
	prog.f.cIm = im;

	prog.win.mlx = mlx_init();
	prog.win.mlx_win = mlx_new_window(prog.win.mlx, prog.pos.w, prog.pos.h, "Fract-ol");
	prog.win.img = mlx_new_image(prog.win.mlx, prog.pos.w, prog.pos.h);
	prog.win.addr = mlx_get_data_addr(prog.win.img, &prog.win.bits_per_pixel, &prog.win.line_length, &prog.win.endian);
	fractal_island(prog.f.set, &prog);
	mlx_mouse_hook(prog.win.mlx_win, woom, &prog.win);
	mlx_hook(prog.win.mlx_win, 17, 0, end_p, &prog.win);
	mlx_key_hook(prog.win.mlx_win, input, &prog.win);
	mlx_loop(prog.win.mlx);
}

int	main(int ac, char *av[])
{
	if (ac < 2 && ac > 5)
		return (putstr(ERROR), -1);
	if (!ft_strncmp(tolow(av[1]), "julia", 5))
	{
		if (ac != 4)
			return (putstr(ERROR), -1);
		p_start('j', aad(av[2]), aad(av[3]));
	}
	if (!ft_strncmp(tolow(av[1]), "mandelbrot", 11))
		p_start('m', 0, 0);
	if (!ft_strncmp(tolow(av[1]), "burningship", 12))
		p_start('b', 0, 0);
	return (0);
}
