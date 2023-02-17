/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:08:34 by minseok2          #+#    #+#             */
/*   Updated: 2023/02/17 20:54:08 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	check_player_is_exist(t_vars *vars)
{
	int		height;
	int		width;

	height = 0;
	while (height < vars->map_height)
	{
		width = 0;
		while (width < vars->map_width)
		{
			if (vars->map_elem[height][width] == PLAYER)
				return ;
			width++;
		}
		height++;
	}
	error_handler(HAVE_NO_PLAYER);
}

static void	check_player_is_duplicated(t_vars *vars)
{
	bool	player_flag;
	int		height;
	int		width;

	player_flag = false;
	height = 0;
	while (height < vars->map_height)
	{
		width = 0;
		while (width < vars->map_width)
		{
			if (vars->map_elem[height][width] == PLAYER)
			{
				if (player_flag == false)
					player_flag = true;
				else
					error_handler(DUPLICATED_PLAYER);
			}
			width++;
		}
		height++;
	}
}

static void	flood_fill(t_map **map, int y, int x, t_ivec map_size)
{
	if (y < 0 || x < 0)
		return ;
	else if (y == map_size.y || x == map_size.x)
		return ;
	else if (map[y][x] == WALL || map[y][x] == VISITED)
		return ;
	else if (map[y][x] == NONE)
		error_handler(UNCLOSED_MAP);
	map[y][x] = VISITED;
	flood_fill(map, y - 1, x, map_size);
	flood_fill(map, y + 1, x, map_size);
	flood_fill(map, y, x - 1, map_size);
	flood_fill(map, y, x + 1, map_size);
}

static void	check_map_is_closed(t_vars *vars)
{
	t_map	**copied_map;
	t_ivec	map_size;

	copied_map = copy_map(vars);
	map_size.y = vars->map_height + 2;
	map_size.x = vars->map_width + 2;
	flood_fill(copied_map, vars->player.y + 1, vars->player.x + 1, map_size);
	free_copied_map(copied_map, map_size);
}

void	validate_map(t_vars *vars)
{
	check_player_is_exist(vars);
	check_player_is_duplicated(vars);
	check_map_is_closed(vars);
}
