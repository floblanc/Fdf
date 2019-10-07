/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maginist <maginist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 10:13:14 by maginist          #+#    #+#             */
/*   Updated: 2019/10/07 13:59:46 by maginist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		ft_error(char *error, int ret, char *after, int line)
{
	char *nb;

	write(2, error, ft_strlen(error));
	if (line > 0)
	{
		nb = ft_itoa(line);
		write(2, nb, ft_strlen(nb));
		free(nb);
	}
	if (after)
		write(2, after, ft_strlen(after));
	return (ret);
}

void	free_stocking(t_stock **start)
{
	t_stock *cur;
	t_stock *before;

	cur = *start;
	while (cur)
	{
		ft_tabdel(cur->data);
		before = cur;
		cur = cur->next;
		free(before);
		before = 0;
	}
}

int		free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->max_y)
	{
		free(map->grid[i]);
		free(map->color[i]);
		i++;
	}
	free(map);
	return (0);
}

void	init_map(t_map *map)
{
	map->name = 0;
	map->color = 0;
	map->error = 0;
	map->grid = 0;
	map->max_x = 0;
	map->max_y = 0;
	map->x1 = 0;
	map->y1 = 0;
	map->mlx_ptr = 0;
	map->wind = 0;
	map->dx = 0;
	map->dy = 0;
	map->dp = 0;
	map->e = 0;
	map->ne = 0;
	map->img = 0;
	map->canvas = 0;
	map->height = 1;
	map->alpha = 0;
	map->beta = 0;
	map->phi = 0;
	map->col_0 = 0;
	map->len_t = 0;
}

int		main(int ac, char **av)
{
	t_map	*map;

	if (ac < 2 || ac > 2)
		return (ft_error("Usage : ./fdf <file.fdf>\n", 0, 0, 0));
	if (!(map = (t_map*)malloc(sizeof(t_map) * 1)))
		return (0);
	init_map(map);
	if (!(parsing_arg(av, map)))
		return (free_map(map));
	map->scale = (970 / map->max_x >= 540 / map->max_y ? 970
	/ map->max_x : 540 / map->max_y);
	map->move_x = 970;
	map->move_y = 540;
	map->mlx_ptr = mlx_init();
	map->wind = mlx_new_window(map->mlx_ptr, 1920, 1080, map->name);
	map->img = mlx_new_image(map->mlx_ptr, 1920, 1080.);
	map->canvas = mlx_get_data_addr(map->img, &(map->bpp)
	, &(map->size_line), &(map->bpp));
	free_stocking(&(map->stock));
	run_fdf(map);
	free_map(map);
	return (0);
}
