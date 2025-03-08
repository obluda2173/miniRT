/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:44:49 by erian             #+#    #+#             */
/*   Updated: 2025/03/08 13:26:00 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	compute_plane_uv(t_vec hit_point, t_plane *plane, double *u, double *v)
{
	t_vec	diff;
	t_vec	up;
	t_vec	tangent;
	t_vec	bitangent;

	diff = sub(hit_point, plane->coordinates);
	up = vec(0, 1, 0);
	if (fabs(dot(up, plane->normal_vector)) > 0.999)
		up = vec(1, 0, 0);
	tangent = normalize(cross(up, plane->normal_vector));
	bitangent = normalize(cross(plane->normal_vector, tangent));
	*u = (dot(diff, tangent) / TEXTURE_SCALE)
		- floor(dot(diff, tangent) / TEXTURE_SCALE);
	*v = (dot(diff, bitangent) / TEXTURE_SCALE)
		- floor(dot(diff, bitangent) / TEXTURE_SCALE);
}

t_color	sample_xpm(t_xpm *xpm, double u, double v)
{
	int	x;
	int	y;

	x = (int)(u * xpm->width) % xpm->width;
	y = (int)(v * xpm->height) % xpm->height;
	if (x < 0)
		x += xpm->width;
	if (y < 0)
		y += xpm->height;
	return (int_to_color(xpm->data[y * xpm->width + x]));
}

t_vec	sample_normal_map(t_xpm *normal_map, double u, double v)
{
	int		x;
	int		y;
	int		color;
	t_vec	n;

	x = (int)(u * normal_map->width) % normal_map->width;
	y = (int)(v * normal_map->height) % normal_map->height;
	if (x < 0)
		x += normal_map->width;
	if (y < 0)
		y += normal_map->height;
	color = normal_map->data[y * normal_map->width + x];
	n.x = (((color >> 16) & 0xFF) / 255.0) * 2.0 - 1.0;
	n.y = (((color >> 8) & 0xFF) / 255.0) * 2.0 - 1.0;
	n.z = ((color & 0xFF) / 255.0) * 2.0 - 1.0;
	return (normalize(n));
}
