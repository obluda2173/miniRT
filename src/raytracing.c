/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:38 by erian             #+#    #+#             */
/*   Updated: 2025/03/05 17:56:22 by erian            ###   ########.fr       */
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
t_ray generate_ray(t_cam *camera, int x, int y)
{
	t_ray ray;
	double aspect_ratio = (double)WIN_WIDTH / WIN_HEIGHT;
	double fov_scale = tan(camera->fov / 2.0 * (M_PI / 180.0));

	// Basis vectors
	t_vec w = normalize(scale(camera->orientation, -1));
	t_vec u = normalize(cross(w, vec(0, 1, 0)));
	t_vec v = cross(w, u);

	// Viewport dimensions
	t_vec horizontal = scale(u, 2.0 * aspect_ratio * fov_scale);
	t_vec vertical = scale(v, 2.0 * fov_scale);
	t_vec lower_left_corner = sub(sub(sub(camera->coordinates, scale(horizontal, 0.5)), scale(vertical, 0.5)), w);

	// Ray calculation
	ray.origin = camera->coordinates;
	t_vec offset = add(scale(horizontal, ((double)x + 0.5) / WIN_WIDTH),
						scale(vertical, ((double)y + 0.5) / WIN_HEIGHT));
	t_vec point_on_viewport = add(lower_left_corner, offset);
	ray.direction = normalize(sub(point_on_viewport, ray.origin));

	return (ray);
}

int process_pixel(t_data *data, int x, int y)
{
	double			t;
	t_ray			ray;
	t_vec			normal;
	t_obj			*closest_obj;
	t_intersection	inter;
	int				color;

	ray = generate_ray(data->scene->camera, x, y);
	closest_obj = find_closest_object(ray, data->scene->obj_lst, &t, &normal);

	if (!closest_obj)
		return (0x000000);

	inter.hit_point = add(ray.origin, scale(ray.direction, t));
	if (dot(normal, ray.direction) > 0)
		normal = scale(normal, -1);
	inter.normal = normal;
	
	if (closest_obj->type == SPHERE)
		inter.base_color = ((t_sphere *)closest_obj->specific_obj)->color;
	if (closest_obj->type == PLANE)
	{
		if ((int)(inter.hit_point.x * 2) % 2 == (int)(inter.hit_point.z * 2) % 2)
			inter.base_color = ((t_plane *)closest_obj->specific_obj)->color;
		else
			inter.base_color = color_scale(((t_plane *)closest_obj->specific_obj)->color, 0.5);
	}
	// to do other objects

	color = apply_ambient_light(inter.base_color, data->scene->a_light);
	color = apply_source_light(data->scene, &inter, color);

	return (color);
}

void render_scene(t_data *data)
{
	int	x;
	int	y;
	int	pixel_color;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			pixel_color = process_pixel(data, x, y);
			mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, pixel_color);
		}
	}
}
