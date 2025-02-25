/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:43:48 by erian             #+#    #+#             */
/*   Updated: 2025/02/25 17:40:32 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void valid_file_name(char *file_name)
{
	if (!(ft_strlen(file_name) >= 4) || !ft_strnstr(file_name, ".rt", ft_strlen(file_name)))
	{
		ft_putstr_fd("Error: Wrong file format. Expected .rt\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void parse(char *file_name, t_data *data)
{
	int fd;

	valid_file_name(file_name);

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		free_and_exit(data, "Error: Cannot open file\n");

	data->obj_lst = extract_objs(fd, data);
	close(fd);
}
