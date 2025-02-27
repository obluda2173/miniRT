/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extracting_objects.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:20:12 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 19:13:42 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t array_size(char **array)
{
    size_t i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}

bool is_valid_number(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]) && str[i] != '.' && str[i] != ',' && str[i] != '-')
            return (false);
        i++;
    }
    return (true);
}

bool is_valid_line(char **split_line)
{
    if (array_size(split_line) == 0)
        return (false);
    if (ft_strcmp(split_line[0], "A") == 0 && array_size(split_line) == 3 && is_valid_number(split_line[1]) && is_valid_number(split_line[2]))
        return (true);
    if (ft_strcmp(split_line[0], "L") == 0 && array_size(split_line) == 4 && is_valid_number(split_line[1]) && is_valid_number(split_line[2]) && is_valid_number(split_line[3]))
        return (true);
    if (ft_strcmp(split_line[0], "C") == 0 && array_size(split_line) == 4 && is_valid_number(split_line[1]) && is_valid_number(split_line[2]) && is_valid_number(split_line[3]))
        return (true);
    if (ft_strcmp(split_line[0], "pl") == 0 && array_size(split_line) == 4 && is_valid_number(split_line[1]) && is_valid_number(split_line[2]) && is_valid_number(split_line[3]))
        return (true);
    if (ft_strcmp(split_line[0], "sp") == 0 && array_size(split_line) == 4 && is_valid_number(split_line[1]) && is_valid_number(split_line[2]) && is_valid_number(split_line[3]))
        return (true);
    if (ft_strcmp(split_line[0], "cy") == 0 && array_size(split_line) == 6 && is_valid_number(split_line[1]) && is_valid_number(split_line[2]) && is_valid_number(split_line[3]) && is_valid_number(split_line[4]) && is_valid_number(split_line[5]))
        return (true);
    return (false);
}

t_color parse_color(char *str, t_data *data)
{
    t_color color;
    char **rgb = ft_split(str, ',');
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

t_vec parse_vector(char *str, t_data *data)
{
    t_vec vec;
    char **xyz = ft_split(str, ',');
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

void extract_objs(int fd, t_data *data)
{
    char *line;
    char **split_line;
    t_scene *scene = data->scene;

    line = get_next_line(fd);
    while (line)
    {
        split_line = ft_split(line, ' ');
        free(line);
        if (!is_valid_line(split_line))
        {
            free_split(split_line);
            data->error = "Error: Invalid line format\n";
            break ;
        }
        if (ft_strcmp(split_line[0], "C") == 0)
            scene->camera = parse_camera(split_line, data);
        if (ft_strcmp(split_line[0], "A") == 0)
            scene->a_light = parse_a_light(split_line, data);
        if (ft_strcmp(split_line[0], "L") == 0)
            ft_lstadd_back(&scene->light_lst, ft_lstnew(parse_s_light(split_line, data)));
        if (ft_strcmp(split_line[0], "pl") == 0)
            ft_lstadd_back(&scene->obj_lst, ft_lstnew(parse_plane(split_line, data)));
        if (ft_strcmp(split_line[0], "sp") == 0)
            ft_lstadd_back(&scene->obj_lst, ft_lstnew(parse_sphere(split_line, data)));
        if (ft_strcmp(split_line[0], "cy") == 0)
            ft_lstadd_back(&scene->obj_lst, ft_lstnew(parse_cylinder(split_line, data)));
        free_split(split_line);
        line = get_next_line(fd);
    }
    if (data->error)
        free_and_exit(data, data->error);
}
