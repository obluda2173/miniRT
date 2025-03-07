/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:43:48 by erian             #+#    #+#             */
/*   Updated: 2025/03/07 14:53:23 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "graphics.h"

static bool	is_valid_filename(char *file_name)
{
	if (!(ft_strlen(file_name) >= 4) || !ft_strnstr(file_name, ".rt", ft_strlen(file_name)))
	{
		ft_putstr_fd("Error: Wrong file format. Expected .rt\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

void	parse_scene(char *filename, t_data *data)
{
	int	fd;

	if (!is_valid_filename(filename))
		exit(EXIT_FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Cannot open file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	data->mlx = ft_calloc(sizeof(t_mlx), 1);
	if (!data->mlx)
		free_and_exit(data, "Error: Failed to allocate MLX struct\n");
	data->mlx->mlx = mlx_init();
	extract_objs(fd, data);
	close(fd);
}
