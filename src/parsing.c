/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:43:48 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 19:10:10 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool is_valid_filename(char *file_name)
{
	if (!(ft_strlen(file_name) >= 4) || !ft_strnstr(file_name, ".rt", ft_strlen(file_name)))
	{
		ft_putstr_fd("Error: Wrong file format. Expected .rt\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

void parse_scene(char *filename, t_data *data)
{
	int fd;

	if (!is_valid_filename(filename))
		exit(EXIT_FAILURE);
	
	fd = open(filename, O_RDONLY);

	if (fd < 0)
	{
		ft_putstr_fd("Error: Cannot open file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}

	extract_objs(fd, data);
	
	close(fd);
}
