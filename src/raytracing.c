/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:38 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 15:22:09 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cam_settings(t_cam *camera, t_cam_settings *cam_set)
{
	t_vec	w;
	t_vec	u;
	t_vec	v;
	double	aspect_ratio;
	double	fov_scale;

	aspect_ratio = (double)WIN_WIDTH / WIN_HEIGHT;
	fov_scale = tan(camera->fov / 2.0 * (M_PI / 180.0));
	w = normalize(scale(camera->orientation, -1));
	u = normalize(cross(w, vec(0, 1, 0)));
	v = cross(w, u);
	cam_set->horizontal = scale(u, 2.0 * aspect_ratio * fov_scale);
	cam_set->vertical = scale(v, 2.0 * fov_scale);
	cam_set->lower_left_corner = sub(sub(sub(camera->coordinates,
					scale(cam_set->horizontal, 0.5)),
				scale(cam_set->vertical, 0.5)), w);
}

t_ray	generate_ray(t_cam *camera, t_cam_settings cam_set, int x, int y)
{
	t_ray	ray;
	t_vec	offset;
	t_vec	point_on_viewport;

	ray.origin = camera->coordinates;
	offset = add(scale(cam_set.horizontal, ((double)x + 0.5) / WIN_WIDTH),
			scale(cam_set.vertical, ((double)y + 0.5) / WIN_HEIGHT));
	point_on_viewport = add(cam_set.lower_left_corner, offset);
	ray.direction = normalize(sub(point_on_viewport, ray.origin));
	return (ray);
}

t_color handle_plane(t_intersection *inter, t_obj *obj)
{
	t_plane *plane = (t_plane *)obj->specific_obj;
	double u, v;
	t_color color;

	compute_plane_uv(inter->hit_point, plane, &u, &v);
	if (plane->texture && plane->normal_map)
	{
		color = sample_xpm(plane->texture, u, v);
		t_vec bump = sample_normal_map(plane->normal_map, u, v);
		t_vec rot_axis = normalize(cross(plane->normal_vector, bump));
		double rot_angle = acos(dot(plane->normal_vector, bump));
		inter->normal = add(add(scale(bump, cos(rot_angle)), scale(cross(rot_axis, bump), sin(rot_angle))), scale(rot_axis, dot(rot_axis, bump) * (1 - cos(rot_angle))));
	}
	else
	{
		color = plane->color;
	}

	return (color);
	// if (((int)floor(inter->hit_point.x * 2) + (int)floor(inter->hit_point.z * 2)) % 2 == 0)
	// 	return color;
	// else
	// 	return color_scale(color, 0.8);
}

int process_pixel(t_data *data, t_cam_settings cam_set, int x, int y)
{
	double          t;
	t_ray           ray;
	t_vec           normal;
	t_obj           *closest_obj;
	t_intersection  inter;

	ray = generate_ray(data->scene->camera, cam_set, x, y);
	closest_obj = find_closest_object(ray, data->scene->obj_lst, &t, &normal);
	if (!closest_obj)
		return (0x000000);
	inter.hit_point = add(ray.origin, scale(ray.direction, t));
	if (dot(normal, ray.direction) > 0)
		normal = scale(normal, -1);
	inter.normal = normal;
	if (closest_obj->type == SPHERE)
		inter.base_color = ((t_sphere *)closest_obj->specific_obj)->color;
	else if (closest_obj->type == PLANE)
		inter.base_color = handle_plane(&inter, closest_obj);
	else if (closest_obj->type == CYLINDER)
		inter.base_color = ((t_cylinder *)closest_obj->specific_obj)->color;
	else if (closest_obj->type == CONE)
		inter.base_color = ((t_cone *)closest_obj->specific_obj)->color;
	return (apply_source_light(data->scene, &inter,
		apply_ambient_light(inter.base_color, data->scene->a_light)));
}

void	render_scene(t_data *data)
{
	int				x;
	int				y;
	int				pixel_color;
	t_cam_settings	cam_set;

	init_cam_settings(data->scene->camera, &cam_set);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			pixel_color = process_pixel(data, cam_set, x, y);
			mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, pixel_color);
		}
	}
}
