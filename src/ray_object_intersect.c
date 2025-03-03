/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_object_intersect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:19:31 by erian             #+#    #+#             */
/*   Updated: 2025/03/03 14:22:24 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*

equation of →P(t) ray:
→P(t) = →O + t * →D

where: 
→O - origin of ray
t - distance from origin to point 
→D - direction of the ray (vector unit)

equation of a sphere with centre →C and radius R:
(→P - →C)^2 = R^2

where: 
→C - centre of sphere
R - radius of sphere 
→P - any point on the surface of the sphere

∴ ((→O + t * →D) - →C)^2 = R^2

let →oc = →O - →C (the vector from ray origin to the sphere centre)

((→oc + t * →D) - →C)^2 = R^2

expands:

t^2 * (→D * →D) + 2t * (→oc * →D) + (→oc * →oc - R^2) = 0

which results in a quadratic equation:

at^2 + bt + c = 0

where:
a = →D * →D
b = 2 * (→oc * →D)
c = →oc * →oc - R^2

roots of the equation are distance to the ray-sphere intersection, 
we are collecting the smallest one since the ray does not penetrate the object

*/
bool ray_sphere_intersect(t_ray ray, t_sphere *sphere, double *t)
{
	t_vec oc = sub(ray.origin, sphere->coordinates);
	double a = dot(ray.direction, ray.direction);
	double b = 2.0 * dot(oc, ray.direction);
	double c = dot(oc, oc) - ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	double discriminant = discr(a, b, c);

	if (discriminant < 0)
		return false;

	double t1 = root_n(a, b, c);
	double t2 = root_p(a, b, c);
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

t_obj *find_closest_object(t_ray ray, t_list *orig_obj_lst, double *closest_t, t_vec *closest_normal)
{
	t_obj *closest_obj = NULL;
	t_list *obj_lst = orig_obj_lst;
	double t;

	*closest_t = INFINITY;
	while (obj_lst)
	{
		t_obj *current = obj_lst->content;
		if (current->type == SPHERE)
		{
			t_sphere *sphere = (t_sphere *)current->specific_obj;
			if (ray_sphere_intersect(ray, sphere, &t) && t < *closest_t)
			{
				*closest_t = t;
				closest_obj = current;
				*closest_normal = normalize(sub(add(ray.origin, scale(ray.direction, t)), sphere->coordinates));
			}
		}
		obj_lst = obj_lst->next;
	}
	return (closest_obj);
}

bool is_in_shadow(t_vec hit_point, t_s_light *light, t_scene *scene)
{
	t_ray shadow_ray;
	t_vec light_dir = sub(light->coordinates, hit_point);
	double light_distance = length(light_dir);

	shadow_ray.origin = add(hit_point, scale(normalize(light_dir), EPSILON));
	shadow_ray.direction = normalize(light_dir);

	double t;
	t_list *current_obj = scene->obj_lst;

	while (current_obj)
	{
		t_obj *obj = current_obj->content;
		if (obj->type == SPHERE && (ray_sphere_intersect(shadow_ray, (t_sphere *)obj->specific_obj, &t)) && (t > EPSILON && t < light_distance)) 	
			return (true);
		// add intersection checks for other object types (planes, cylinders etc.)
		current_obj = current_obj->next;
	}
	return (false);
}
