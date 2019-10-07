/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:13:19 by floblanc          #+#    #+#             */
/*   Updated: 2019/10/05 12:28:14 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		red_cross(t_map *map)
{
	free_map(map);
	exit(0);
	return (0);
}

void	write_pixel(t_map *map, int x, int y, int i)
{
	if (y >= 0 && y <= 1080 && x >= 0 && x <= 1920)
		*(int *)&map->canvas[y * map->size_line + (x * 4)] = map->color[i
		/ map->max_x][i % map->max_x];
}

void	write_segs(t_map *map, int x, int y, int i)
{
	write_pixel(map, x, y, i);
	map->col_0 = map->color[i / map->max_x][i % map->max_x];
	if (i / map->max_x < map->max_y - 1)
		select_seg_sens(map, x, y, i + map->max_x);
	if ((i + 1) % map->max_x)
		select_seg_sens(map, x, y, i + 1);
}

void	run_fdf(t_map *map)
{
	int		i;
	double	x;
	double	y;
	double	z;

	i = -1;
	x = 0;
	y = 0;
	z = 0;
	ft_bzero(map->canvas, 4 * 1920 * 1080);
	while (++i / map->max_x < map->max_y)
	{
		calc_alpha(&y, &z, i, map);
		calc_beta(&x, &z, i, map);
		calc_phi(&x, &y, i, map);
		write_segs(map, x, y, i);
	}
	mlx_put_image_to_window(map->mlx_ptr, map->wind, map->img, 0, 0);
	write_hud(map);
	mlx_hook(map->wind, 17, 0, red_cross, map);
	mlx_hook(map->wind, 2, 0, key_act, map);
	mlx_loop(map->mlx_ptr);
}
