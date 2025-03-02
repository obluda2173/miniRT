/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:38 by erian             #+#    #+#             */
/*   Updated: 2025/03/02 15:08:41 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*

The generated ray equation:

→P(t) = →O + t * →D

where: 
→O - origin of the ray (camera position)
→D - direction of the ray
t - distance from origin to point

The viewport is a plane in front of the camera. 
Each pixel (x, y) on the screen corresponds to a point on this plane.

To calculate the ray:
1. Compute the camera basis vectors:
	- →w: inverted camera direction (pointing backward)
	- →u: right vector (perpendicular to both w and world up)
	- →v: up vector (perpendicular to both w and u)
2. Compute viewport dimensions:
	- aspect_ratio: width / height
	- fov_scale: tan(fov / 2) determines how large the viewport appears
	- horizontal and vertical span the viewport in world space
3. Compute the lower-left corner of the viewport.
4. Compute the ray direction by interpolating between the viewport edges.

*/
t_ray	generate_ray(t_cam *camera, int x, int y)
{
	t_ray	ray;
	double	aspect_ratio = (double)WIN_WIDTH / WIN_HEIGHT;
	double	fov_scale = tan(camera->fov / 2.0 * (M_PI / 180.0));

	// Basis vectors
	t_vec	w = normalize(scale(camera->orientation, -1));
	t_vec	u = normalize(cross(w, vec(0, 1, 0)));
	t_vec	v = cross(u, w);

	// Viewport dimensions
	t_vec	horizontal = scale(u, 2.0 * aspect_ratio * fov_scale);
	t_vec	vertical = scale(v, 2.0 * fov_scale);
	t_vec	lower_left_corner = sub(sub(sub(camera->coordinates, scale(horizontal, 0.5)), scale(vertical, 0.5)), w);

	// Ray calculation
	ray.origin = camera->coordinates;
	t_vec offset = add(scale(horizontal, (double)x / WIN_WIDTH), 
						scale(vertical, (double)y / WIN_HEIGHT));
	t_vec point_on_viewport = add(lower_left_corner, offset);
	ray.direction = normalize(sub(point_on_viewport, ray.origin));

	return (ray);
}


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
	if (discriminant < 0)
		return (false);
	t1 = root_n(a, b, c);
	t2 = root_p(a, b, c);
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

void	render_scene(t_data *data)
{
	int			x;
	int			y;
	double		t;
	t_ray		ray;
	t_sphere	*sphere;
	t_a_light	*a_light;
	t_s_light	*s_light;
	int			color;
	t_vec		hit_point, normal;

	sphere = (t_sphere *)get_specific_obj(data->scene->obj_lst, SPHERE);
	a_light = (t_a_light *)data->scene->a_light;
	s_light = (t_s_light *)get_specific_obj(data->scene->light_lst, S_LIGHT);
	if (!sphere)
	{
		ft_putstr_fd("Error: Sphere not found\n", STDERR_FILENO);
		return;
	}
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray = generate_ray(data->scene->camera, x, y);
			
			if (ray_sphere_intersect(ray, sphere, &t))
			{
				// Compute hit point and normal
				hit_point = add(ray.origin, scale(ray.direction, t));
				normal = normalize(sub(hit_point, sphere->coordinates));

				// Apply lighting (ambient + light source)
				color = apply_ambient_light(sphere->color, a_light);
				color = apply_light_source(int_to_color(color), s_light, hit_point, normal);
				
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, color);
			}
			else
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
