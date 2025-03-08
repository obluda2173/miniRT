/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:37:01 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 11:32:06 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		free_data(data);
		exit(0);
	}
	return (0);
}

int	close_hook(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}

void	init_window(t_data *data)
{
	if (!data->mlx->mlx)
		free_and_exit(data, "Error: MLX initialization failed\n");
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIN_WIDTH,
			WIN_HEIGHT, "miniRT");
	if (!data->mlx->win)
		free_and_exit(data, "Error: Failed to create window\n");
	mlx_hook(data->mlx->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->mlx->win, 17, 1L << 17, close_hook, data);
}
