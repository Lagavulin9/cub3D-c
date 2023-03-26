/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:14:20 by minseok2          #+#    #+#             */
/*   Updated: 2023/02/24 13:41:34 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	cub3d_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx_ptr, vars->background.img);
	mlx_destroy_image(vars->mlx_ptr, vars->view.img);
	mlx_destroy_image(vars->mlx_ptr, vars->minimap.background_img.img);
	mlx_destroy_image(vars->mlx_ptr, vars->minimap.img.img);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init(&vars, argc, argv);
	mlx_hook(vars.win_ptr, X_EVENT_KEY_PRESS, 0, &key_press, &vars);
	mlx_hook(vars.win_ptr, X_EVENT_KEY_EXIT, 0, &cub3d_exit, &vars);
	mlx_loop_hook(vars.mlx_ptr, &mouse, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
