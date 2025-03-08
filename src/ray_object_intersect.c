/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:31 by erian             #+#    #+#             */
/*   Updated: 2025/03/07 14:13:55 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "operations.h"
#include "raytracing.h"

bool	ray_sphere_intersect(t_ray ray, t_sphere *sphere, double *t)
{
	t_quadratic_coeff coeff;
	t_vec oc = sub(ray.origin, sphere->coordinates);
	coeff.a = dot(ray.direction, ray.direction);
	coeff.b = 2.0 * dot(oc, ray.direction);
	coeff.c = dot(oc, oc) - ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	double discriminant = discr(coeff);
	if (discriminant < 0)
		return (false);

	double t1 = root_n(coeff);
	double t2 = root_p(coeff);


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

t_obj	*find_closest_object(t_ray ray, t_list *orig_obj_lst, double *closest_t, t_vec *closest_normal)
{
	t_obj	*closest_obj;
	t_list	*obj_lst;
	t_obj	*obj_node;
	double	t;

	closest_obj = NULL;
	obj_lst = orig_obj_lst;
	*closest_t = INFINITY;
	while (obj_lst)
	{
		obj_node = obj_lst->content;
		if (obj_node->type == CYLINDER) {
			t_cylinder *cy = (t_cylinder *)obj_node->specific_obj;
			t_cy_inter *cy_inter = ray_inter_cylinder(ray, *cy);
			if (cy_inter)
			{
				if(cy_inter->t < *closest_t)
				{
					*closest_t = cy_inter->t;
					closest_obj = obj_node;
					*closest_normal = calc_normal_cy(ray, cy, cy_inter);
				}
				free(cy_inter);
			}
		}
		if (obj_node->type == CONE)
		{
			t_cone *cone = (t_cone *)obj_node->specific_obj;
			if (ray_inf_cone_intersect(ray, cone, &t) && t < *closest_t)
			{
				*closest_t = t;
				closest_obj = obj_node;

				t_vec X = sub(ray.origin, cone->apex);
				t_vec hit_p = add(ray.origin, scale(ray.direction, t));
				t_vec p_minus_c = sub(hit_p, cone->apex);
				double one_plus_k_squared = (1 + (tan(cone->alpha) * tan(cone->alpha)));
				double m = dot(ray.direction, cone->axis) * t + dot(X, cone->axis);
				*closest_normal = normalize(sub(p_minus_c, scale(cone->axis, one_plus_k_squared * m)));
			}
		}
		if (obj_node->type == SPHERE)
		{
			t_sphere *sphere = (t_sphere *)obj_node->specific_obj;
			if (ray_sphere_intersect(ray, sphere, &t) && t < *closest_t)
			{
				*closest_t = t;
				closest_obj = obj_node;
				*closest_normal = normalize(sub(add(ray.origin, scale(ray.direction, t)), sphere->coordinates));
			}
		}
		if (obj_node->type == PLANE)
		{
			t_plane *plane = (t_plane *)obj_node->specific_obj;
			if (ray_plane_intersect(ray, plane, &t) && t < *closest_t)
			{
				*closest_t = t;
				closest_obj = obj_node;
				*closest_normal = plane->normal_vector;
			}
		}
		// add other objects
		obj_lst = obj_lst->next;
	}
	return (closest_obj);
}

bool	is_in_shadow(t_vec hit_point, t_s_light *light, t_scene *scene)
{
	t_ray	shadow_ray;
	t_vec	light_dir;
	double	light_distance;
	double	t;
	t_list	*current_obj;
	t_obj	*obj;

	light_dir = sub(light->coordinates, hit_point);
	light_distance = length(light_dir);
	shadow_ray.origin = add(hit_point, scale(normalize(light_dir), EPSILON));
	shadow_ray.direction = normalize(light_dir);
	current_obj = scene->obj_lst;

	while (current_obj)
	{
		obj = current_obj->content;
		if (obj->type == SPHERE && (ray_sphere_intersect(shadow_ray, (t_sphere *)obj->specific_obj, &t)) && (t > EPSILON && t < light_distance))
			return (true);
		if (obj->type == PLANE && (ray_plane_intersect(shadow_ray, (t_plane *)obj->specific_obj, &t)) && (t > EPSILON && t < light_distance))
			return (true);
		if (obj->type == CONE && (ray_inf_cone_intersect(shadow_ray, (t_cone *)obj->specific_obj, &t)) && (t > EPSILON && t < light_distance))
			return (true);
		if (obj->type == CYLINDER)
		{
			t_cylinder *cy = (t_cylinder *)obj->specific_obj;
			t_cy_inter *cy_inter = ray_inter_cylinder(shadow_ray, *cy);
			if (cy_inter)
			{
				if (cy_inter->t < light_distance)
				{
					free(cy_inter);
					return true;
				}
				free(cy_inter);
			}
		}
		current_obj = current_obj->next;
	}
	return (false);
}
