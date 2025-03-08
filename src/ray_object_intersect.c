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

typedef struct s_closest_params {
	double* closest_t;
	t_vec* closest_normal;
	t_obj** closest_obj;
} t_closest_params;



void update_t_plane(t_ray ray, t_cl *cl, t_obj *obj_node) {
	double t;
	t_plane *plane = (t_plane *)obj_node->specific_obj;
	if (ray_plane_intersect(ray, plane, &t) && t < cl->t)
	{
		cl->t = t;
		cl->obj = obj_node;
		cl->normal = plane->normal_vector;
	}
}

t_cl	find_closest_object(t_ray ray, t_list *orig_obj_lst)
{
	t_list		*obj_lst;
	t_obj		*obj_node;
	double		t;
	t_cylinder	*cy;
	t_cy_inter	*cy_inter;
	t_cone		*cone;
	t_vec		X;
	t_vec		hit_p;
	t_vec		p_minus_c;
	double		one_plus_k_squared;
	double		m;
	t_sphere	*sphere;
	t_cl cl;

	cl.obj = NULL;
	cl.t = INFINITY;
	obj_lst = orig_obj_lst;
	while (obj_lst)
	{
		obj_node = obj_lst->content;
		if (obj_node->type == CYLINDER)
		{
			cy = (t_cylinder *)obj_node->specific_obj;
			cy_inter = ray_inter_cylinder(ray, *cy);
			if (cy_inter)
			{
				if (cy_inter->t < cl.t)
				{
					cl.t = cy_inter->t;
					cl.obj = obj_node;
					cl.normal = calc_normal_cy(ray, cy, cy_inter);
				}
				free(cy_inter);
			}
		}
		if (obj_node->type == CONE)
		{
			cone = (t_cone *)obj_node->specific_obj;
			if (ray_inf_cone_intersect(ray, cone, &t) && t < cl.t)
			{
				cl.t = t;
				cl.obj = obj_node;
				X = sub(ray.origin, cone->apex);
				hit_p = add(ray.origin, scale(ray.direction, t));
				p_minus_c = sub(hit_p, cone->apex);
				one_plus_k_squared = (1 + (tan(cone->alpha)
							* tan(cone->alpha)));
				m = dot(ray.direction, cone->axis) * t + dot(X, cone->axis);
				cl.normal = normalize(sub(p_minus_c, scale(cone->axis,
								one_plus_k_squared * m)));
			}
		}
		if (obj_node->type == SPHERE)
		{
			sphere = (t_sphere *)obj_node->specific_obj;
			if (ray_sphere_intersect(ray, sphere, &t) && t < cl.t)
			{
				cl.t = t;
				cl.obj = obj_node;
				cl.normal = normalize(sub(add(ray.origin,
								scale(ray.direction, t)), sphere->coordinates));
			}
		}
		if (obj_node->type == PLANE)
			update_t_plane(ray, &cl, obj_node);
		obj_lst = obj_lst->next;
	}
	return cl;
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
