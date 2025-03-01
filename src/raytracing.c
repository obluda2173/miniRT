/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:51:38 by erian             #+#    #+#             */
/*   Updated: 2025/03/01 14:57:03 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"
#include "minirt.h"
#include "operations.h"

#define EPSILON 1e-6

t_ray	generate_ray(t_cam *camera, int x, int y)
{
    t_ray	ray;
    double	aspect_ratio;
    double	fov_scale;
    t_vec	w;
    t_vec	u;
    t_vec	v;
    t_vec	horizontal;
    t_vec	vertical;
    t_vec	lower_left_corner;

    aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
    fov_scale = tan(camera->fov / 2.0 * (M_PI / 180.0));

    // Calculate camera basis vectors
    w = normalize(scale(camera->orientation, -1));
    u = normalize(cross(vec(0, 1, 0), w)); // Right
    v = cross(w, u); // Up

    horizontal = scale(u, 2.0 * aspect_ratio * fov_scale);
    vertical = scale(v, 2.0 * fov_scale);
    lower_left_corner = sub(sub(sub(camera->coordinates, scale(horizontal, 0.5)), scale(vertical, 0.5)), w);

    ray.origin = camera->coordinates;
    ray.direction.x = ((double)x / WIN_WIDTH) * horizontal.x + ((double)y / WIN_HEIGHT) * vertical.x - lower_left_corner.x;
    ray.direction.y = ((double)x / WIN_WIDTH) * horizontal.y + ((double)y / WIN_HEIGHT) * vertical.y - lower_left_corner.y;
    ray.direction.z = ((double)x / WIN_WIDTH) * horizontal.z + ((double)y / WIN_HEIGHT) * vertical.z - lower_left_corner.z;
    ray.direction = normalize(ray.direction);

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
