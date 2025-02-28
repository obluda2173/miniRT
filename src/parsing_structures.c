/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_structures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:25:00 by erian             #+#    #+#             */
/*   Updated: 2025/02/28 13:00:54 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_obj_type	get_obj_type(t_list *obj_lst)
{
	if (!obj_lst || !obj_lst->content)
		return (-1);
	return (*((t_obj_type *)obj_lst->content));
}

t_cam	*parse_camera(char **split_line, t_data *data)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	cam->type = CAMERA;
	cam->coordinates = parse_vector(split_line[1], data);
	cam->orientation = parse_vector(split_line[2], data);
	cam->fov = ft_atoi(split_line[3]);
	if (cam->orientation.x < -1 || cam->orientation.x > 1
		|| cam->orientation.y < -1 || cam->orientation.y > 1
		|| cam->orientation.z < -1 || cam->orientation.z > 1)
		data->error = "Error: Invalid orientation vector range\n";
	if (cam->fov < 0 || cam->fov > 180)
		data->error = "Error: Invalid fov range\n";
	return (cam);
}

t_a_light	*parse_a_light(char **split_line, t_data *data)
{
	t_a_light	*a_light;

	a_light = malloc(sizeof(t_a_light));
	a_light->type = A_LIGHT;
	a_light->ratio = ft_atod(split_line[1]);
	a_light->color = parse_color(split_line[2], data);
	if (a_light->ratio < 0 || a_light->ratio > 1)
		data->error = "Error: Invalid ambient light ratio range\n";
	return (a_light);
}

t_s_light	*parse_s_light(char **split_line, t_data *data)
{
	t_s_light	*s_light;

	s_light = malloc(sizeof(t_s_light));
	s_light->type = S_LIGHT;
	s_light->coordinates = parse_vector(split_line[1], data);
	s_light->ratio = ft_atod(split_line[2]);
	s_light->color = parse_color(split_line[3], data);
	if (s_light->ratio < 0 || s_light->ratio > 1)
		data->error = "Error: Invalid source light ratio range\n";
	return (s_light);
}

t_plane	*parse_plane(char **split_line, t_data *data)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	plane->type = PLANE;
	plane->coordinates = parse_vector(split_line[1], data);
	plane->normal_vector = parse_vector(split_line[2], data);
	plane->color = parse_color(split_line[3], data);
	if (plane->normal_vector.x < -1 || plane->normal_vector.x > 1
		|| plane->normal_vector.y < -1 || plane->normal_vector.y > 1
		|| plane->normal_vector.z < -1 || plane->normal_vector.z > 1)
		data->error = "Error: Invalid plane normal vector range\n";
	return (plane);
}

t_sphere	*parse_sphere(char **split_line, t_data *data)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	sphere->type = SPHERE;
	sphere->coordinates = parse_vector(split_line[1], data);
	sphere->diameter = ft_atod(split_line[2]);
	sphere->color = parse_color(split_line[3], data);
	return (sphere);
}

t_cylinder	*parse_cylinder(char **split_line, t_data *data)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	cylinder->type = CYLINDER;
	cylinder->coordinates = parse_vector(split_line[1], data);
	cylinder->normal_vector = parse_vector(split_line[2], data);
	cylinder->diameter = ft_atod(split_line[3]);
	cylinder->height = ft_atod(split_line[4]);
	cylinder->color = parse_color(split_line[5], data);
	if (cylinder->normal_vector.x < -1 || cylinder->normal_vector.x > 1
		|| cylinder->normal_vector.y < -1 || cylinder->normal_vector.y > 1
		|| cylinder->normal_vector.z < -1 || cylinder->normal_vector.z > 1)
		data->error = "Error: Invalid cylinder normalized vector range\n";
	return (cylinder);
}
