/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texures.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:44:49 by erian             #+#    #+#             */
/*   Updated: 2025/03/06 18:39:26 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void compute_plane_uv(t_vec hit_point, t_plane *plane, double *u, double *v)
{
	double texture_scale = 15.0;

	t_vec diff = sub(hit_point, plane->coordinates);
	t_vec up = {0, 1, 0};
	if (fabs(dot(up, plane->normal_vector)) > 0.999)
		up = (t_vec){1, 0, 0};
	t_vec tangent = normalize(cross(up, plane->normal_vector));
	t_vec bitangent = normalize(cross(plane->normal_vector, tangent));
	double u_val = dot(diff, tangent) / texture_scale;
	double v_val = dot(diff, bitangent) / texture_scale;
	*u = u_val - floor(u_val);
	*v = v_val - floor(v_val);
}

t_color sample_xpm(t_xpm *xpm, double u, double v)
{
	int x = (int)(u * xpm->width) % xpm->width;
	int y = (int)(v * xpm->height) % xpm->height;
	if (x < 0) 
		x += xpm->width;
	if (y < 0)
		y += xpm->height;
	return int_to_color(xpm->data[y * xpm->width + x]);
}

t_vec sample_normal_map(t_xpm *normal_map, double u, double v)
{
	int x = (int)(u * normal_map->width) % normal_map->width;
	int y = (int)(v * normal_map->height) % normal_map->height;
	if (x < 0) x += normal_map->width;
	if (y < 0) y += normal_map->height;
	int color = normal_map->data[y * normal_map->width + x];
	
	double r = ((color >> 16) & 0xFF) / 255.0;
	double g = ((color >> 8) & 0xFF) / 255.0;
	double b = (color & 0xFF) / 255.0;
	
	t_vec n;
	n.x = r * 2.0 - 1.0;
	n.y = g * 2.0 - 1.0;
	n.z = b * 2.0 - 1.0;
	return normalize(n);
}
