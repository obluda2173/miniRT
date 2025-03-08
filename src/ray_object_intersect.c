/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:31 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 16:37:40 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ray_sphere_intersect(t_ray ray, t_sphere *sphere, double *t)
{
	t_quadratic_coeff	coeff;
	t_vec				oc;
	double				discriminant;
	double				t1;
	double				t2;

	oc = sub(ray.origin, sphere->coordinates);
	coeff.a = dot(ray.direction, ray.direction);
	coeff.b = 2.0 * dot(oc, ray.direction);
	coeff.c = dot(oc, oc) - ((sphere->diameter / 2.0) * (sphere->diameter
				/ 2.0));
	discriminant = discr(coeff);
	if (discriminant < 0)
		return (false);
	t1 = root_n(coeff);
	t2 = root_p(coeff);
	if (t1 > EPSILON && t2 > EPSILON)
		*t = fmin(t1, t2);
	else if (t1 > EPSILON)
		*t = t1;
	else if (t2 > EPSILON)
		*t = t2;
	else
		return (false);
	return (true);
}

bool	ray_plane_intersect(t_ray ray, t_plane *plane, double *t)
{
	double	denominator;
	t_vec	origin_to_plane;

	denominator = dot(plane->normal_vector, ray.direction);
	if (fabs(denominator) > EPSILON)
	{
		origin_to_plane = sub(plane->coordinates, ray.origin);
		*t = dot(origin_to_plane, plane->normal_vector) / denominator;
		return (*t >= 0);
	}
	return (false);
}

t_cl	find_closest_object(t_ray ray, t_list *orig_obj_lst)
{
	t_list	*obj_lst;
	t_obj	*obj_node;
	t_cl	cl;

	cl.obj = NULL;
	cl.t = INFINITY;
	obj_lst = orig_obj_lst;
	while (obj_lst)
	{
		obj_node = obj_lst->content;
		if (obj_node->type == CYLINDER)
			update_cl_cyl(ray, &cl, obj_node);
		if (obj_node->type == CONE)
			update_cl_cone(ray, &cl, obj_node);
		if (obj_node->type == SPHERE)
			update_cl_sphere(ray, &cl, obj_node);
		if (obj_node->type == PLANE)
			update_cl_plane(ray, &cl, obj_node);
		obj_lst = obj_lst->next;
	}
	return (cl);
}

bool	check_object_intersection(t_ray s_ray, t_obj *obj, double max_t)
{
	bool		result;
	double		t;
	t_cy_inter	*cy_inter;

	if (obj->type == SPHERE && ray_sphere_intersect(s_ray,
			(t_sphere *)obj->specific_obj, &t))
		return (t > EPSILON && t < max_t);
	if (obj->type == PLANE && ray_plane_intersect(s_ray,
			(t_plane *)obj->specific_obj, &t))
		return (t > EPSILON && t < max_t);
	if (obj->type == CONE && ray_inf_cone_intersect(s_ray,
			(t_cone *)obj->specific_obj, &t))
		return (t > EPSILON && t < max_t);
	if (obj->type == CYLINDER)
	{
		cy_inter = ray_inter_cylinder(s_ray, *(t_cylinder *)obj->specific_obj);
		if (cy_inter)
		{
			result = (cy_inter->t < max_t);
			free(cy_inter);
			return (result);
		}
	}
	return (false);
}

bool	is_in_shadow(t_vec hit_point, t_s_light *light, t_scene *scene)
{
	t_ray	s_ray;
	t_list	*current_obj;
	double	max_t;

	s_ray.direction = normalize(sub(light->coordinates, hit_point));
	s_ray.origin = add(hit_point, scale(normalize(s_ray.direction), EPSILON));
	max_t = length(s_ray.direction);
	current_obj = scene->obj_lst;
	while (current_obj)
	{
		if (check_object_intersection(s_ray, current_obj->content, max_t))
			return (true);
		current_obj = current_obj->next;
	}
	return (false);
}
