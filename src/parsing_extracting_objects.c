/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extracting_objects.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:20:12 by erian             #+#    #+#             */
/*   Updated: 2025/02/26 11:35:57 by erian            ###   ########.fr       */
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

bool valid_number(char *str)
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
    if (ft_strcmp(split_line[0], "A") == 0 && array_size(split_line) == 3 && valid_number(split_line[1]) && valid_number(split_line[2]))
        return (true);
    if (ft_strcmp(split_line[0], "L") == 0 && array_size(split_line) == 4 && valid_number(split_line[1]) && valid_number(split_line[2]) && valid_number(split_line[3]))
        return (true);
    if (ft_strcmp(split_line[0], "C") == 0 && array_size(split_line) == 4 && valid_number(split_line[1]) && valid_number(split_line[2]) && valid_number(split_line[3]))
        return (true);
    if (ft_strcmp(split_line[0], "pl") == 0 && array_size(split_line) == 4 && valid_number(split_line[1]) && valid_number(split_line[2]) && valid_number(split_line[3]))
        return (true);
    if (ft_strcmp(split_line[0], "sp") == 0 && array_size(split_line) == 4 && valid_number(split_line[1]) && valid_number(split_line[2]) && valid_number(split_line[3]))
        return (true);
    if (ft_strcmp(split_line[0], "cy") == 0 && array_size(split_line) == 5 && valid_number(split_line[1]) && valid_number(split_line[2]) && valid_number(split_line[3]) && valid_number(split_line[4]))
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

t_obj *extract_objs(int fd, t_data *data)
{
    char *line;
    char **split_line;
    t_obj *obj_lst = NULL;
    t_obj *new_obj;

    line = get_next_line(fd);
    while (line)
    {
        split_line = ft_split(line, ' ');
        if (!split_line)
        {
            free(line);
            free_and_exit(data, "Error: Memory allocation failed\n");
        }

        if (array_size(split_line) > 0)
        {
            if (!is_valid_line(split_line))
            {
                free_split(split_line);
                free(line);
                free_and_exit(data, "Error: Invalid line format\n");
            }
            new_obj = malloc(sizeof(t_obj));
            if (!new_obj)
            {
                free_split(split_line);
                free(line);
                free_and_exit(data, "Error: Memory allocation failed\n");
            }
            if (ft_strcmp(split_line[0], "A") == 0)
                new_obj->type = A_LIGHT, new_obj->obj = parse_a_light(split_line, data);
            else if (ft_strcmp(split_line[0], "L") == 0)
                new_obj->type = S_LIGHT, new_obj->obj = parse_s_light(split_line, data);
            else if (ft_strcmp(split_line[0], "C") == 0)
                new_obj->type = CAMERA, new_obj->obj = parse_camera(split_line, data);
            else if (ft_strcmp(split_line[0], "pl") == 0)
                new_obj->type = PLANE, new_obj->obj = parse_plane(split_line, data);
            else if (ft_strcmp(split_line[0], "sp") == 0)
                new_obj->type = SPHERE, new_obj->obj = parse_sphere(split_line, data);
            else if (ft_strcmp(split_line[0], "cy") == 0)
                new_obj->type = CYLINDER, new_obj->obj = parse_cylinder(split_line, data);
            else
                free(new_obj), new_obj = NULL;

            if (new_obj)
            {
                new_obj->next = obj_lst;
                obj_lst = new_obj;
            }
        }
        free_split(split_line);
        free(line);
        line = get_next_line(fd);
    }
    return obj_lst;
}
