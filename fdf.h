/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:26:19 by jmabel            #+#    #+#             */
/*   Updated: 2022/05/17 21:35:01 by jmabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

# include "mlx.h"
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

/*  set default colors for lowest and highest altitude */
# define LOW_COLOR 0x9900cc
# define HIGH_COLOR 0xffff00

/*  set default window size */
# define WIDTH 1024
# define HEIGHT 1024

/* set mlx events */
# define ON_KEYDOWN 2
# define ON_DESTROY 17

/* set keycode */
# define ESC 53

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_matrix
{
	float	a11;
	float	a12;
	float	a13;
	float	a21;
	float	a22;
	float	a23;
	float	a31;
	float	a32;
	float	a33;
}	t_matrix;

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
	int	c;
}	t_coord;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			**map;
	int			**color;
	int			column;
	int			row;
	int			max_alt;
	int			min_alt;
	t_img		img;
	t_matrix	m;
	t_coord		angle;
	t_coord		zoom;
}	t_fdf;

typedef struct s_pars
{
	char	*line;
	char	**map_line;
	char	**cell;
	int		fd;	
}	t_pars;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

/* fdf.c */
int			ft_fdf_close(t_fdf *fdf);

/* map_read.c */
void		ft_read_map(t_fdf *fdf, int argc, char **argv);

/* map_define_value.c */
void		ft_define_map_value(t_fdf *fdf, t_pars *parser, int nb_line);
void		ft_define_zoom(t_fdf *fdf);
void		ft_define_rotate_angle(t_fdf *fdf);

/* map_error.c  */
void		ft_exit_fdf(char error);
void		ft_error_map_close(t_pars *parser, char error);
void		ft_error_map(t_pars *parser, char error);
void		ft_error_allocate_arr(t_fdf *fdf, t_pars *parser, char error);
void		ft_error_allocate_cell(t_fdf *fdf, t_pars *parser, char error);

/* array_operations.c */
void		ft_free_int_array(int **arr, int len);
void		ft_free_char_array(char **arr);
int			ft_count_column(char const *s, char c);

/*  ft_atoi_base10.c  */
int			ft_atoi_base_10(t_fdf *fdf, t_pars *parser, char *str);

/* ft_atoi_base16.c */
int			ft_atoi_base_16(t_fdf *fdf, t_pars *parser, char *str);

/* colors.c */
void		ft_set_colors(t_fdf *fdf);
void		ft_hex_to_rgb(int color, t_rgb *rgb);

/* put_image.c */
void		ft_mlx_pixel_put_img(t_img	*img, int x, int y, int color);

/* line.c */
void		ft_line_gradient_color(t_img *img, t_coord p0, t_coord p1);

/* matrix_operations.c */
t_matrix	ft_scale_matrix(t_coord zoom);
t_matrix	ft_identity_matrix(void);
t_matrix	ft_matrix_multiply(t_matrix X, t_matrix Y);

/* matrix_rotate.c */
t_matrix	ft_rotate(t_coord	angle);

/* draw.c */
void		ft_draw_map(t_fdf *fdf);

/* hook.c */
void		ft_hook(t_fdf *fdf);

#endif