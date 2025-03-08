/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object_intersect_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:26/55 by kfreyer           #+#    #+#             */
/*   Updated: 2025/03/08 17:26:55 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_cl_plane(t_ray ray, t_cl *cl, t_obj *obj_node)
{
	double	t;
	t_plane	*plane;

	plane = (t_plane *)obj_node->specific_obj;
	if (ray_plane_intersect(ray, plane, &t) && t < cl->t)
	{
		cl->t = t;
		cl->obj = obj_node;
		cl->normal = plane->normal_vector;
	}
}

void	update_cl_sphere(t_ray ray, t_cl *cl, t_obj *obj_node)
{
	double		t;
	t_sphere	*sphere;

	sphere = (t_sphere *)obj_node->specific_obj;
	if (ray_sphere_intersect(ray, sphere, &t) && t < cl->t)
	{
		cl->t = t;
		cl->obj = obj_node;
		cl->normal = normalize(sub(add(ray.origin, scale(ray.direction, t)),
					sphere->coordinates));
	}
}

void	update_cl_cone(t_ray ray, t_cl *cl, t_obj *obj_node)
{
	double	one_plus_k_squared;
	t_vec	p_minus_c;
	double	t;
	double	m;
	t_cone	*cone;

	cone = (t_cone *)obj_node->specific_obj;
	if (ray_inf_cone_intersect(ray, cone, &t) && t < cl->t)
	{
		cl->t = t;
		cl->obj = obj_node;
		p_minus_c = sub(add(ray.origin, scale(ray.direction, t)), cone->apex);
		one_plus_k_squared = (1 + (tan(cone->alpha) * tan(cone->alpha)));
		m = dot(ray.direction, cone->axis) * t + dot(sub(ray.origin,
					cone->apex), cone->axis);
		cl->normal = normalize(sub(p_minus_c, scale(cone->axis,
						one_plus_k_squared * m)));
	}
}

void	update_cl_cyl(t_ray ray, t_cl *cl, t_obj *obj_node)
{
	t_cylinder	*cy;
	t_cy_inter	*cy_inter;

	cy = (t_cylinder *)obj_node->specific_obj;
	cy_inter = ray_inter_cylinder(ray, *cy);
	if (cy_inter)
	{
		if (cy_inter->t < cl->t)
		{
			cl->t = cy_inter->t;
			cl->obj = obj_node;
			cl->normal = calc_normal_cy(ray, cy, cy_inter);
		}
		free(cy_inter);
	}
}
