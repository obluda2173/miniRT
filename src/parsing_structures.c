/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_structures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:25:00 by erian             #+#    #+#             */
/*   Updated: 2025/03/04 12:27:04 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// not currently used
void	*get_specific_obj(t_list *obj_lst, t_obj_type type)
{
	t_list	*tmp_obj_lst;

	tmp_obj_lst = obj_lst;
	while (tmp_obj_lst)
	{
		t_obj *obj = (t_obj *)tmp_obj_lst->content;
		if (obj->type == type)
			return obj->specific_obj;
		tmp_obj_lst = tmp_obj_lst->next;
	}
	return (NULL);
}

// not currently used
t_obj_type get_obj_type(t_list *obj_lst)
{
	t_obj	*obj;

	obj = (t_obj *)obj_lst->content;
	return (obj->type);
}

t_cam	*parse_camera(char **split_line, t_data *data)
{
	t_cam	*cam;

	cam = malloc(sizeof(t_cam));
	if (!cam)
		free_and_exit(data, "Error: Memory allocation failed for camera\n");
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
	if (!a_light)
		free_and_exit(data, "Error: Memory allocation failed for ambient light\n");
	a_light->ratio = ft_atod(split_line[1]);
	a_light->color = parse_color(split_line[2], data);
	if (a_light->ratio < 0 || a_light->ratio > 1)
		data->error = "Error: Invalid ambient light ratio range\n";
	return (a_light);
}

t_obj	*parse_s_light(char **split_line, t_data *data)
{
	t_s_light	*s_light;
	t_obj		*obj;

	s_light = malloc(sizeof(t_s_light));
	if (!s_light)
		free_and_exit(data, "Error: Memory allocation failed for source light\n");
	s_light->coordinates = parse_vector(split_line[1], data);
	s_light->ratio = ft_atod(split_line[2]);
	s_light->color = parse_color(split_line[3], data);
	obj = malloc(sizeof(t_obj));
	if (!obj)
		free_and_exit(data, "Error: Memory allocation failed for t_object\n");
	if (s_light->ratio < 0 || s_light->ratio > 1)
		data->error = "Error: Invalid source light ratio range\n";
	obj->type = S_LIGHT;
	obj->specific_obj = s_light;
	return (obj);
}

t_obj	*parse_plane(char **split_line, t_data *data)
{
	t_plane	*plane;
	t_obj	*obj;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		free_and_exit(data, "Error: Memory allocation failed for plane\n");
	plane->coordinates = parse_vector(split_line[1], data);
	plane->normal_vector = parse_vector(split_line[2], data);
	plane->color = parse_color(split_line[3], data);
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
	cylinder->normal_vector = parse_vector(split_line[2], data);
	cylinder->diameter = ft_atod(split_line[3]);
	cylinder->height = ft_atod(split_line[4]);
	cylinder->color = parse_color(split_line[5], data);
	obj = malloc(sizeof(t_obj));
	if (!obj)
		free_and_exit(data, "Error: Memory allocation failed for t_object\n");
	if (cylinder->normal_vector.x < -1 || cylinder->normal_vector.x > 1
		|| cylinder->normal_vector.y < -1 || cylinder->normal_vector.y > 1
		|| cylinder->normal_vector.z < -1 || cylinder->normal_vector.z > 1)
		data->error = "Error: Invalid cylinder normalized vector range\n";
	obj->type = CYLINDER;
	obj->specific_obj = cylinder;
	return (obj);
}
