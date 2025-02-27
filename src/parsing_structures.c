/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_structures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:25:00 by erian             #+#    #+#             */
/*   Updated: 2025/02/27 19:52:37 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_obj_type get_obj_type(t_list *obj_lst)
{
    if (!obj_lst || !obj_lst->content)
        return -1;

    return *((t_obj_type *)obj_lst->content);
}

t_a_light *parse_a_light(char **split_line, t_data *data)
{
    if (array_size(split_line) != 3)
        data->error = "Error: Invalid ambient light format\n";
    t_a_light *a_light = malloc(sizeof(t_a_light));
    a_light->type = A_LIGHT;
    a_light->ratio = ft_atod(split_line[1]);
    a_light->color = parse_color(split_line[2], data);
    return (a_light);
}

t_s_light *parse_s_light(char **split_line, t_data *data)
{
    if (array_size(split_line) != 4)
        data->error = "Error: Invalid source light format\n";
    t_s_light *s_light = malloc(sizeof(t_s_light));
    s_light->type = S_LIGHT;
    s_light->coordinates = parse_vector(split_line[1], data);
    s_light->ratio = ft_atod(split_line[2]);
    s_light->color = parse_color(split_line[3], data);
    return (s_light);
}

t_cam *parse_camera(char **split_line, t_data *data)
{
    if (array_size(split_line) != 4)
        data->error = "Error: Invalid camera format\n";
    t_cam *cam = malloc(sizeof(t_cam));
    cam->type = CAMERA;
    cam->coordinates = parse_vector(split_line[1], data);
    cam->orientation = parse_vector(split_line[2], data);
    cam->fov = ft_atoi(split_line[3]);
    return (cam);
}

t_plane *parse_plane(char **split_line, t_data *data)
{
    if (array_size(split_line) != 4)
        data->error = "Error: Invalid plane format\n";
    t_plane *plane = malloc(sizeof(t_plane));
    plane->type = PLANE;
    plane->coordinates = parse_vector(split_line[1], data);
    plane->normal_vector = parse_vector(split_line[2], data);
    plane->color = parse_color(split_line[3], data);
    return (plane);
}

t_sphere *parse_sphere(char **split_line, t_data *data)
{
    if (array_size(split_line) != 4)
        data->error = "Error: Invalid sphere format\n";
    t_sphere *sphere = malloc(sizeof(t_sphere));
    sphere->type = SPHERE;
    sphere->coordinates = parse_vector(split_line[1], data);
    sphere->diameter = ft_atod(split_line[2]);
    sphere->color = parse_color(split_line[3], data);
    return (sphere);
}

t_cylinder *parse_cylinder(char **split_line, t_data *data)
{
    if (array_size(split_line) != 6)
        data->error = "Error: Invalid cylinder format\n";
    t_cylinder *cylinder = malloc(sizeof(t_cylinder));
    cylinder->type = CYLINDER;
    cylinder->coordinates = parse_vector(split_line[1], data);
    cylinder->normal_vector = parse_vector(split_line[2], data);
    cylinder->diameter = ft_atod(split_line[3]);
    cylinder->height = ft_atod(split_line[4]);
    cylinder->color = parse_color(split_line[5], data);
    return (cylinder);
}
