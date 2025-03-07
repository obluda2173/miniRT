/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:29:44 by erian             #+#    #+#             */
/*   Updated: 2025/03/07 16:55:16 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", STDERR_FILENO);
		return (1);
	}
	parse_scene(av[1], &data);
	init_window(&data);
	render_scene(&data);
	mlx_loop(data.mlx->mlx);
	free_data(&data);
	return (0);
}
