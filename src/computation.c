/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:45:27 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/07 11:18:16 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		calc_color(t_map *m, int x0, int y0, int i)
{
	double	div;
	int		red_d;
	int		green_d;
	int		blue_d;
	int		res;

	div = ((double)m->len_t - sqrt(pow(m->x1 - x0, 2) + pow(m->y1 - y0, 2)))
	/ (double)m->len_t;
	red_d = (m->color[i / m->max_x][i % m->max_x] & 0xFF0000)
	- (m->col_0 & 0xFF0000);
	red_d = (int)(red_d * div);
	green_d = (m->color[i / m->max_x][i % m->max_x] & 0xFF00)
	- (m->col_0 & 0xFF00);
	green_d = (int)(green_d * div);
	blue_d = (m->color[i / m->max_x][i % m->max_x] & 0xFF)
	- (m->col_0 & 0xFF);
	blue_d = (int)(blue_d * div);
	res = m->col_0;
	res += (red_d - red_d % 0x10000) + (green_d - green_d % 0x100) + blue_d;
	return (res);
}

void	calc_alpha(double *y, double *z, int i, t_map *map)
{
	*y = ((i / map->max_x - map->max_y / 2) * cos(map->alpha)
		- map->grid[i / map->max_x][i % map->max_x] * map->height
		* sin(map->alpha)) * map->scale;
	*z = (i / map->max_x - map->max_y / 2) * sin(map->alpha)
		+ map->grid[i / map->max_x][i % map->max_x] * map->height
		* cos(map->alpha);
}

void	calc_beta(double *x, double *z, int i, t_map *map)
{
	*x = ((i % map->max_x - map->max_x / 2) * cos(map->beta)
		+ *z * sin(map->beta)) * map->scale;
	*z = -(i % map->max_x - map->max_x / 2) * sin(map->beta)
		+ *z * cos(map->beta);
}

void	calc_phi(double *x, double *y, int i, t_map *map)
{
	int	x_save;

	(void)i;
	x_save = *x;
	*x = (x_save * cos(map->phi) - *y * sin(map->phi)) + map->move_x;
	*y = (x_save * sin(map->phi) + *y * cos(map->phi)) + map->move_y;
}
