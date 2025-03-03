/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:38 by erian             #+#    #+#             */
/*   Updated: 2025/03/03 11:55:50 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool ray_sphere_intersect(t_ray ray, t_sphere *sphere, double *t);

t_ray generate_ray(t_cam *camera, int x, int y)
{
	t_ray ray;
	double aspect_ratio = (double)WIN_WIDTH / WIN_HEIGHT;
	double fov_scale = tan(camera->fov / 2.0 * (M_PI / 180.0));

	// Basis vectors
	t_vec w = normalize(scale(camera->orientation, -1));
	t_vec u = normalize(cross(vec(0, 1, 0), w));
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

	return ray;
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
	return closest_obj;
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

	while (current_obj) {
		t_obj *obj = current_obj->content;
		if (obj->type == SPHERE) {
			if (ray_sphere_intersect(shadow_ray, (t_sphere *)obj->specific_obj, &t))
			{
				if (t > EPSILON && t < light_distance)
				{
					return true;
				}
			}
		}
		// add intersection checks for other object types (planes, cylinders etc.)
		current_obj = current_obj->next;
	}
	return false;
}

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
		return false;

	return true;
}

void render_scene(t_data *data)
{
	int x, y;
	t_ray ray;
	t_vec hit_point, normal;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			double t;
			t_obj *closest_obj = NULL;
			ray = generate_ray(data->scene->camera, x, y);
			closest_obj = find_closest_object(ray, data->scene->obj_lst, &t, &normal);

			if (closest_obj)
			{
				hit_point = add(ray.origin, scale(ray.direction, t));
				if (dot(normal, ray.direction) > 0)
					normal = scale(normal, -1);

				t_color final_color = int_to_color(apply_ambient_light(
					((t_sphere *)closest_obj->specific_obj)->color,
					data->scene->a_light)
				);

				t_list *light_lst = data->scene->light_lst;
				while (light_lst)
				{
					t_obj *light_obj = light_lst->content;
					if (light_obj->type == S_LIGHT)
					{
						t_s_light *light = (t_s_light *)light_obj->specific_obj;
						if (!is_in_shadow(hit_point, light, data->scene))
						{
							t_color light_contrib = calculate_light(
								light,
								hit_point,
								normal,
								((t_sphere *)closest_obj->specific_obj)->color
							);
							final_color = color_add(final_color, light_contrib);
						}
					}
					light_lst = light_lst->next;
				}

				final_color = color_clamp(final_color);
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, 
							color_to_int(final_color));
			}
			else
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, 0x000000);
		}
	}
}



