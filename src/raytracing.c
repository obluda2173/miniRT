/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:38 by erian             #+#    #+#             */
/*   Updated: 2025/03/01 11:41:56 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "minirt.h"
#include "operations.h"

#define M_PI 3.14159265358979323846

t_ray	generate_ray(t_cam *camera, int x, int y)
{
	t_ray	ray;
	double	aspect_ratio;
	double	fov_scale;

	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	fov_scale = tan(camera->fov / 2.0 * (M_PI / 180.0));

	ray.origin = camera->coordinates;
	ray.direction.x = (2 * ((x + 0.5) / WIN_WIDTH) - 1) * aspect_ratio * fov_scale;
	ray.direction.y = (1 - 2 * ((y + 0.5) / WIN_HEIGHT)) * fov_scale;
	ray.direction.z = -1;
	ray.direction = normalize(ray.direction);

	return (ray);
}

// ray-sphere intersection
bool	ray_sphere_intersect(t_ray ray, t_sphere *sphere, double *t)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;

	oc = sub(ray.origin, sphere->coordinates);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(oc, ray.direction);
	c = dot(oc, oc) - ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = discr(a, b, c);
	if (discr < 0)
		return (false);
	t1 = root_n(a, b, c);
	t1 = root_p(a, b, c);
	if (t1 > 0)
		*t = t1;
	else if (t2 > 0)
		*t = t2;
	else
		return (false);
	return (true);
}
