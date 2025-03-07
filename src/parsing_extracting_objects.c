/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extracting_objects.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:20:12 by erian             #+#    #+#             */
/*   Updated: 2025/03/07 16:54:35 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	array_size(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

t_color	parse_color(char *str, t_data *data)
{
	t_color	color;
	char	**rgb;

	rgb = ft_split(str, ',');
	if (!rgb || array_size(rgb) != 3)
	{
		free_split(rgb);
		free_and_exit(data, "Error: Invalid color format\n");
	}
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255)
		data->error = "Error: Invalid color range\n";
	free_split(rgb);
	return (color);
}

t_vec	parse_vector(char *str, t_data *data)
{
	t_vec	vec;
	char	**xyz;

	xyz = ft_split(str, ',');
	if (!xyz || array_size(xyz) != 3)
	{
		free_split(xyz);
		free_and_exit(data, "Error: Invalid vector format\n");
	}
	vec.x = ft_atod(xyz[0]);
	vec.y = ft_atod(xyz[1]);
	vec.z = ft_atod(xyz[2]);
	free_split(xyz);
	return (vec);
}

void	extract_objs(int fd, t_data *data)
{
	char	*line;
	char	**split_line;

	data->scene = ft_calloc(sizeof(t_scene), 1);
	if (!data->scene)
		free_and_exit(data, "Error: Memory allocation failed\n");

	data->error = NULL;

	line = get_next_line(fd);
	while (line)
	{
		if ((line && line[0] == '\0') || line[0] == '#' || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		char *line_trimmed = ft_strtrim(line, "\n");
		split_line = ft_split(line_trimmed, ' ');
		free(line_trimmed);
		free(line);
		if (ft_strcmp(split_line[0], "C") == 0 && c_check(split_line, data) && data->scene->c_count++ == 0)
			data->scene->camera = parse_camera(split_line, data);
		else if (ft_strcmp(split_line[0], "A") == 0 && a_check(split_line, data) && data->scene->a_count++ == 0)
			data->scene->a_light = parse_a_light(split_line, data);
		else if (ft_strcmp(split_line[0], "L") == 0 && l_check(split_line, data))
			ft_lstadd_back(&data->scene->light_lst, ft_lstnew(parse_s_light(split_line, data)));
		else if (ft_strcmp(split_line[0], "pl") == 0 && pl_check(split_line, data))
			ft_lstadd_back(&data->scene->obj_lst, ft_lstnew(parse_plane(split_line, data)));
		else if (ft_strcmp(split_line[0], "sp") == 0 && sp_check(split_line, data))
			ft_lstadd_back(&data->scene->obj_lst, ft_lstnew(parse_sphere(split_line, data)));
		else if (ft_strcmp(split_line[0], "cy") == 0 && cy_check(split_line, data))
			ft_lstadd_back(&data->scene->obj_lst, ft_lstnew(parse_cylinder(split_line, data)));
		else if (ft_strcmp(split_line[0], "co") == 0 && co_check(split_line, data))
			ft_lstadd_back(&data->scene->obj_lst, ft_lstnew(parse_cone(split_line, data)));
		else
			data->error = "Error: Invalid object format\n";
		free_split(split_line);
		line = get_next_line(fd);
	}
	if (data->error || data->scene->c_count != 1 || data->scene->a_count != 1)
	{
		free_stash(fd);
		free_and_exit(data, data->error);
	}
}
