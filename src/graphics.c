/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:37:01 by erian             #+#    #+#             */
/*   Updated: 2025/03/01 13:52:22 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "graphics.h"
#include "utils.h"

#define ESC 65307

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	return (0);
}

int	close_hook(t_data *data)
{
	close_window(data);
	return (0);
}

void	init_window(t_data *data)
{
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->mlx)
		free_and_exit(data, "Error: Failed to allocate MLX struct\n");
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		free_and_exit(data, "Error: MLX initialization failed\n");
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!data->mlx->win)
		free_and_exit(data, "Error: Failed to create window\n");

	mlx_hook(data->mlx->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->mlx->win, 17, 1L << 17, close_hook, data);
}

void	close_window(t_data *data)
{
	if (data->mlx->win)
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	if (data->mlx->mlx)
	{
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx->mlx);
	}
	free_data(data);
	exit(0);
}
