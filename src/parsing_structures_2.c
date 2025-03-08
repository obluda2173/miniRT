/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_structures_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:25:00 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 13:11:55 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_obj	*parse_plane(char **split_line, t_data *data)
{
	t_plane	*plane;
	t_obj	*obj;

	plane = ft_calloc(sizeof(t_plane), 1);
	if (!plane)
		free_and_exit(data, "Error: Memory allocation failed for plane\n");
	plane->coordinates = parse_vector(split_line[1], data);
	plane->normal_vector = parse_vector(split_line[2], data);
	plane->color = parse_color(split_line[3], data);
	if (array_size(split_line) == 6)
	{
		plane->texture = parse_xpm(split_line[4], data);
		plane->normal_map = parse_xpm(split_line[5], data);
	}
	obj = malloc(sizeof(t_obj));
	if (!obj)
		free_and_exit(data, "Error: Memory allocation failed for t_object\n");
	if (plane->normal_vector.x < -1 || plane->normal_vector.x > 1
		|| plane->normal_vector.y < -1 || plane->normal_vector.y > 1
		|| plane->normal_vector.z < -1 || plane->normal_vector.z > 1)
		data->error = "Error: Invalid plane normal vector range\n";
	obj->type = PLANE;
	obj->specific_obj = plane;
	return (obj);
}

t_obj	*parse_sphere(char **split_line, t_data *data)
{
	t_sphere	*sphere;
	t_obj		*obj;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		free_and_exit(data, "Error: Memory allocation failed for sphere\n");
	sphere->coordinates = parse_vector(split_line[1], data);
	sphere->diameter = ft_atod(split_line[2]);
	sphere->color = parse_color(split_line[3], data);
	obj = malloc(sizeof(t_obj));
	if (!obj)
		free_and_exit(data, "Error: Memory allocation failed for t_object\n");
	obj->type = SPHERE;
	obj->specific_obj = sphere;
	return (obj);
}

t_obj	*parse_cylinder(char **split_line, t_data *data)
{
	t_cylinder	*cylinder;
	t_obj		*obj;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		free_and_exit(data, "Error: Memory allocation failed for cylinder\n");
	cylinder->coordinates = parse_vector(split_line[1], data);
	cylinder->axis_vector = parse_vector(split_line[2], data);
	cylinder->diameter = ft_atod(split_line[3]);
	cylinder->height = ft_atod(split_line[4]);
	cylinder->color = parse_color(split_line[5], data);
	obj = malloc(sizeof(t_obj));
	if (!obj)
		free_and_exit(data, "Error: Memory allocation failed for t_object\n");
	if (cylinder->axis_vector.x < -1 || cylinder->axis_vector.x > 1
		|| cylinder->axis_vector.y < -1 || cylinder->axis_vector.y > 1
		|| cylinder->axis_vector.z < -1 || cylinder->axis_vector.z > 1)
		data->error = "Error: Invalid cylinder normalized vector range\n";
	obj->type = CYLINDER;
	obj->specific_obj = cylinder;
	return (obj);
}

t_obj	*parse_cone(char **split_line, t_data *data)
{
	t_cone	*cone;
	t_obj	*obj;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		free_and_exit(data, "Error: Memory allocation failed for cylinder\n");
	cone->apex = parse_vector(split_line[1], data);
	cone->axis = normalize(parse_vector(split_line[2], data));
	cone->alpha = ft_atod(split_line[3]);
	if (cone->alpha > 89 || cone->alpha < 1)
	{
		free(cone);
		free_and_exit(data, "Error: Not-valid cone angle\n");
	}
	cone->alpha = (cone->alpha / 180) * M_PI;
	cone->color = parse_color(split_line[4], data);
	obj = malloc(sizeof(t_obj));
	if (!obj)
		free_and_exit(data, "Error: Memory allocation failed for t_object\n");
	obj->type = CONE;
	obj->specific_obj = cone;
	return (obj);
}
