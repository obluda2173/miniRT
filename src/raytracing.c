/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:38 by erian             #+#    #+#             */
/*   Updated: 2025/03/07 13:19:14 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray generate_ray(t_cam *camera, int x, int y)
{
	t_ray ray;
	double aspect_ratio = (double)WIN_WIDTH / WIN_HEIGHT;
	double fov_scale = tan(camera->fov / 2.0 * (M_PI / 180.0));

	t_vec w = normalize(scale(camera->orientation, -1));
	t_vec u = normalize(cross(w, vec(0, 1, 0)));
	t_vec v = cross(w, u);

	t_vec horizontal = scale(u, 2.0 * aspect_ratio * fov_scale);
	t_vec vertical = scale(v, 2.0 * fov_scale);
	t_vec lower_left_corner = sub(sub(sub(camera->coordinates, scale(horizontal, 0.5)), scale(vertical, 0.5)), w);

	ray.origin = camera->coordinates;
	t_vec offset = add(scale(horizontal, ((double)x + 0.5) / WIN_WIDTH),
						scale(vertical, ((double)y + 0.5) / WIN_HEIGHT));
	t_vec point_on_viewport = add(lower_left_corner, offset);
	ray.direction = normalize(sub(point_on_viewport, ray.origin));

	return (ray);
}

t_color	apply_checkerboard(t_intersection *inter, t_color color)
{
	if (((int)floor(inter->hit_point.x * 2) + (int)floor(inter->hit_point.z * 2)) % 2 == 0)
		return (color);
	else
		return (color_scale(color, 0.8));
}

int process_pixel(t_data *data, int x, int y)
{
	double			t;
	t_ray			ray;
	t_vec			normal;
	t_obj			*closest_obj;
	t_intersection	inter;
	int				color;
	double			u, v;

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
		t_plane *plane = (t_plane *)closest_obj->specific_obj;
		compute_plane_uv(inter.hit_point, plane, &u, &v);
		if (plane->texture && plane->normal_map)
		{
			inter.base_color = sample_xpm(plane->texture, u, v);
			inter.normal = sample_normal_map(plane->normal_map, u, v);
		}
		else
			inter.base_color = plane->color;
		// else
			// inter.base_color = apply_checkerboard(&inter, plane->color);
	}
	if (closest_obj->type == CYLINDER)
		inter.base_color = ((t_cylinder *)closest_obj->specific_obj)->color;

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
