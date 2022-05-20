/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:41:47 by jmabel            #+#    #+#             */
/*   Updated: 2022/05/20 21:42:26 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	ft_transform_matrix(t_fdf *fdf)
{
	fdf->m = ft_rotate(fdf->angle);
	fdf->m = ft_matrix_multiply(ft_scale_matrix(fdf->zoom), fdf->m);
}

static int	ft_define_point_coord(t_fdf *fdf, t_coord *p, int x, int y)
{
	int	temp_x;

	(*p).x = x - (fdf->column / 2);
	(*p).y = y - (fdf->row / 2);
	temp_x = (*p).x;
	(*p).x = fdf->m.a11 * (*p).x + fdf->m.a12 * (*p).y
		+ fdf->m.a13 * fdf->map[y][x];
	(*p).y = fdf->m.a21 * temp_x + fdf->m.a22 * (*p).y
		+ fdf->m.a23 * fdf->map[y][x];
	(*p).x = (*p).x + WIDTH / 2;
	(*p).y = (*p).y + HEIGHT / 2;
	(*p).c = fdf->color[y][x];
	if ((*p).x < 0 || (*p).x > WIDTH || (*p).y < 0 || (*p).y > HEIGHT)
		return (-1);
	return (0);
}

static void	ft_draw_lines(t_fdf *fdf, t_coord *step)
{
	t_coord	p0;
	t_coord	p1;

	if (ft_define_point_coord(fdf, &p0, (*step).x, (*step).y) == 0)
	{
		if ((*step).x < fdf->column - 1)
		{
			if (ft_define_point_coord(fdf, &p1, (*step).x + 1, (*step).y) == 0)
				ft_line_gradient_color(&(fdf->img), p0, p1);
		}
		if ((*step).y < (fdf->row - 1))
		{
			if (ft_define_point_coord(fdf, &p1, (*step).x, (*step).y + 1) == 0)
				ft_line_gradient_color(&(fdf->img), p0, p1);
		}
	}
}

static void	ft_draw_tips(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 0, 0xFFFFFF,
		"You can change the map in this ways: ");
}

void	ft_draw(t_fdf *fdf)
{
	t_coord	step;

	ft_transform_matrix(fdf);
	step.y = 0;
	while (step.y < fdf->row)
	{
		step.x = 0;
		while (step.x < fdf->column)
		{
			ft_draw_lines(fdf, &step);
			step.x++;
		}
		step.y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img.img, 0, 0);
	ft_draw_tips(fdf);
	mlx_destroy_image(fdf->mlx_ptr, fdf->img.img);
}