/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:38 by erian             #+#    #+#             */
/*   Updated: 2025/03/01 15:43:23 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "minirt.h"
#include "operations.h"

#define EPSILON 1e-6

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
	t_vec offset = add(scale(horizontal, (double)x/WIN_WIDTH), 
						scale(vertical, (double)y/WIN_HEIGHT));
	t_vec point_on_viewport = add(lower_left_corner, offset);
	ray.direction = normalize(sub(point_on_viewport, ray.origin));

	return (ray);
}

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
	int	x;
	int y;
	double	t;
	t_ray	ray;
	t_sphere	*sphere;

	sphere = (t_sphere *)get_specific_obj(data->scene->obj_lst, SPHERE);
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
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, 0xFFFFFF);
			else
				mlx_pixel_put(data->mlx->mlx, data->mlx->win, x, y, 0x000000);
			x++;
		}
		y++;
	}
}
